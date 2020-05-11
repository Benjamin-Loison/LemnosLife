#define GLEW_STATIC
#include <glew.h>
#include <map>
#include <vector>
#ifdef _WIN32
    #include <windows.h>
#endif
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>

#include "../../StringPlus/string_plus.h"
#include "../../MathPlus/math_plus.h"
#include "../../FilePlus/file_plus.h"
#include "../../Logger/logger.h"
#include "../Main/main.h"
#include "../../FilePlus/configuration.h"
#include "Chunk/Chunk.h"
#include "map.h"
#include "objects.h"
#include "../../3D/Collision/collision.h"
#include "../Render/Gui/Gui/GuiGame.h"
#include "../Render/Gui/Gui/GuiStructures.h"
#include "../Render/Gui/Gui/GuiChat.h"
#include "User/User.h"

using namespace std;

//Global variables TODO : make cleaner
vector<string> strucIdDbStr; // STRUC MAP ARMA SIZE
vector<bool> strucIdDbBool; // STRUC MAP ARMA SIZE
vector<short> linkStrucVec; // STRUC MAP ARMA SIZE
vector<Structure> strucIdDbStruc; // STRUC MODELIZED SIZE

map<int, vector<glm::vec3>> strucTranslations;
map<int, vector<glm::vec3>> strucRotations;
map<int, bool> strucTranslationsToInit;

void loadStructures()
{
    strucIdDbStr.clear();
    strucIdDbBool.clear();
    linkStrucVec.clear();
    strucIdDbStruc.clear();
    strucTranslations.clear();

    string strucFilePath = commonMapFolder + strucIdDbFileName;
    vector<string> lines = getFileContent(strucFilePath);
    for(unsigned short lineIndex = 0; lineIndex < lines.size(); lineIndex++)
    {
        vector<string> parts = split(lines[lineIndex]);
        strucIdDbStr.push_back(parts[1]);
    }
    for(unsigned short strucIdDbIndex = 0; strucIdDbIndex < strucIdDbStr.size(); strucIdDbIndex++)
    {
        string strucFile = structuresFolder + convertNbToStr(strucIdDbIndex) + STRUCTURE_FILE_EXTENSION;
        //print(convertNbToStr(strucIdDbIndex));
        ///if(file_exists(strucFile))
        {
            //print("Y " + convertNbToStr(strucIdDbStruc.size()));
            strucIdDbBool.push_back(true);
            linkStrucVec.push_back(strucIdDbStruc.size());
            strucIdDbStruc.push_back(Structure(strucFile));
            vector<glm::vec3> tmp;
            strucTranslations[strucIdDbIndex] = tmp;
        }
        /*else // used to be usefull but doesn't seems to be likewise can reload not existing model
        {
            //print("N");
            strucIdDbBool.push_back(false);
            linkStrucVec.push_back(-1);
        }*/
    }
}

void reloadStructures()
{
    strucIdDbStr.clear();
    strucIdDbBool.clear();
    linkStrucVec.clear();
    strucIdDbStruc.clear();
    strucTranslations.clear();

    string strucFilePath = commonMapFolder + strucIdDbFileName;
    // print("a0");
    vector<string> lines = getFileContent(strucFilePath);
    for(unsigned short lineIndex = 0; lineIndex < lines.size(); lineIndex++)
    {
        vector<string> parts = split(lines[lineIndex]);
        strucIdDbStr.push_back(parts[1]);
    }
    //print("a2");
    for(unsigned short strucIdDbIndex = 0; strucIdDbIndex < strucIdDbStr.size(); strucIdDbIndex++) /// TO OPTIMIZE
    {
        string strucFile = structuresFolder + convertNbToStr(strucIdDbIndex) + STRUCTURE_FILE_EXTENSION;
        if(file_exists(strucFile))
        {
            strucIdDbBool.push_back(true);
            linkStrucVec.push_back(strucIdDbStruc.size());
            strucIdDbStruc.push_back(Structure(strucFile));
            vector<glm::vec3> tmp;
            strucTranslations[strucIdDbIndex] = tmp;
        }
        else
        {
            strucIdDbBool.push_back(false);
            linkStrucVec.push_back(-1);
        }
    }
    //print("a3");
}

bool isAnATM(unsigned short structureId) // not used
{
    return structureId == ID_ATM_COVERED || structureId == ID_ATM_NOT_COVERED;
}

bool lookingAnATM(unsigned short targetId, unsigned short targetSubId)
{
    return (targetId == ID_ATM_COVERED && targetSubId == 11) || (targetId == ID_ATM_NOT_COVERED && targetSubId == 11); // have to be changed when model will changed
}

#define MAX_STRUCTURE_HYPOTENUSE 10
/// used to be 50
// should save this constant in a file
#define RANGE_TO_CHECK INTERACTION_RANGE + MAX_STRUCTURE_HYPOTENUSE
// should also care at where are eyes on person

Vector3D rotationAndTranslation(Vector3D vec, Vector3D middle, double angle) // little, big // angles: https://community.bistudio.com/wiki/setDir 0: North, 90: East
{
    double r = Vector2D(vec).length(), theta = 0; // oh le con, c'était: Vector2D(Vector2D(vec), Vector2D(middle)).length();
    if(r != 0)
    {
        if(vec.X != 0)
        {
            theta = acos(vec.X / r);
            if(vec.Y < 0)
                theta *= -1;
        }
        else if(vec.Y > 0)
            theta = M_PI / 2;
        else if(vec.Y < 0)
            theta = -M_PI / 2;
    }
    //print("theta: " + convertNbToStr(theta) + " " + convertNbToStr(angle) + " ! " + toString(vec));
    //print("angleRad: " + convertNbToStr(getRadians(angle)) + " theta: " + convertNbToStr(theta) + " vec: " + toString(vec) + " r: " + convertNbToStr(r));
    double finalAngle = -getRadians(angle) + theta/* - M_PI / 2*/;//angle / 2 + theta + M_PI / 2; /// used to be - M_PI /2
    vec.X = r * cos/*sin*/(finalAngle);
    vec.Y = r * sin/*cos*/(finalAngle);
    vec += middle;
    //print(toString(vec));
    return vec; // double con: used to be: middle + vec with + middle.X lines up...
}

Vector3D isRectangleInTarget(Vector3D A, Vector3D B, Vector3D C, Vector3D D, bool descendingFromFoot, bool descending, Vector3D from) /// need special order ?
{
    Vector3D interPt = Vector3D(-1, -1, -1);
    bool res = false;
    if(descendingFromFoot)
        res = rayPickingFromFoot(A, B, C, D, &interPt, descending, from);
    else
        res = rayPicking(A, B, C, D, &interPt);

    return res ? interPt : /* is default value changed if rayPicking false ? It seems so*/ Vector3D(-1, -1, -1);
}

double getMaxRadius(vector<glm::vec3> vertices) // should be stored ?
{
    double maxRadius = 0;
    for(unsigned int verticesIndex = 0; verticesIndex < vertices.size(); verticesIndex++)
    {
        double radius = Vector3D(vertices[verticesIndex]).length();
        if(radius > maxRadius)
        {
            maxRadius = radius;
        }
    }
    return maxRadius;
}

double getMaxRadiusStructures() // cf (42)
{

}

tuple<unsigned short, short, unsigned short, vector<double>, unsigned short, Vector3D> getStructureIdTargetingPos(bool descendingFromFoot, double x, double y, double z, bool descending) // return nearest structure in target // not well manage if exactly on multiple chunks ?
{ /// for x y z could also work with a vector<double> but seems to be too much syntax heavy - used to be double, double, double
    // INTERACTION_RANGE value 8
    /// WILL CHECK DISTANCE TO ALL STRUCTURES IN CURRENT CHUNK
    // CHECK 1 square range chunk around (1000m)

    vector<string> chkToCheck;
    chkToCheck.push_back(getChunkName(x, y));

    double rangeToCheck = RANGE_TO_CHECK;

    if(descendingFromFoot)
    {
        rangeToCheck = MAX_STRUCTURE_HYPOTENUSE;
    }

    double relativeX = remainderEuclidianDivision(x, get<DOUBLE>(mapData)["chunkGroundSize"]); // MANAGE LEFT AND RIGHT CHUNKS
    bool left = false, right = false, up = false, down = false;
    if(relativeX <= rangeToCheck)
    {
        left = true;
        chkToCheck.push_back(getChunkName(x - get<DOUBLE>(mapData)["chunkGroundSize"], y));
    }
    else if(relativeX >= get<DOUBLE>(mapData)["chunkGroundSize"] - rangeToCheck)
    {
        right = true;
        chkToCheck.push_back(getChunkName(x + get<DOUBLE>(mapData)["chunkGroundSize"], y));
    }

    double relativeY = remainderEuclidianDivision(x, get<DOUBLE>(mapData)["chunkGroundSize"]); // MANAGE UP AND DOWN CHUNKS
    if(relativeY <= rangeToCheck)
    {
        down = true; // is inversed ?
        chkToCheck.push_back(getChunkName(x, y - get<DOUBLE>(mapData)["chunkGroundSize"]));
    }
    else if(relativeY >= get<DOUBLE>(mapData)["chunkGroundSize"] - rangeToCheck)
    {
        up = true;
        chkToCheck.push_back(getChunkName(x, y + get<DOUBLE>(mapData)["chunkGroundSize"]));
    }

     // MANAGE DIAGONALS CHUNKS

     if(left)
     {
         if(up)
         {
             chkToCheck.push_back(getChunkName(x - get<DOUBLE>(mapData)["chunkGroundSize"], y + get<DOUBLE>(mapData)["chunkGroundSize"]));
         }
         else if(down)
         {
             chkToCheck.push_back(getChunkName(x - get<DOUBLE>(mapData)["chunkGroundSize"], y - get<DOUBLE>(mapData)["chunkGroundSize"]));
         }
     }
     else if(right) // both left and right shouldn't be able to be on true at the same time
     {
         if(up)
         {
             chkToCheck.push_back(getChunkName(x + get<DOUBLE>(mapData)["chunkGroundSize"], y + get<DOUBLE>(mapData)["chunkGroundSize"]));
         }
         else if(down)
         {
             chkToCheck.push_back(getChunkName(x + get<DOUBLE>(mapData)["chunkGroundSize"], y - get<DOUBLE>(mapData)["chunkGroundSize"]));
         }
     }

     //vector<tuple<unsigned short, Vector3D, unsigned short>> structures;
     // generate parts of structures in real time or generate them at startup (first option here)
     double interactionRange = INTERACTION_RANGE;///, rangeToCheck = RANGE_TO_CHECK;
     if(descendingFromFoot)
     {
         // if ppow(10, 1) bug for big structures like basketball playground
         interactionRange = pow(10, 2); /// should make kind of cube root
         ///rangeToCheck = pow(10, 1);
     }
     double minDistance = interactionRange;
    unsigned short structureIdNearestTarget = UNSIGNED_SHORT_MAX, finalAngle = 0;
    short partIndex = -1;
    //pair<double, double> p[4];
    vector<double> coordinatesDebug;
    Vector3D vecPos = Vector3D(x, y, z), finalVec;
    for(unsigned short chkToCheckIndex = 0; chkToCheckIndex < chkToCheck.size(); chkToCheckIndex++)
    {
        //print("Chk: " + convertNbToStr(chkToCheckIndex));
        string currentChkToCheck = chkToCheck[chkToCheckIndex];
        //print("name: " + currentChkToCheck);
        Chunk chk = chunksLoaded[currentChkToCheck];
        for(map<int, Structure>::iterator it = chk.m_structures.begin(); it != chk.m_structures.end(); it++) // why structure "propre" to a chunk ? (42)
        {
            //print("s: " + convertNbToStr(it->first));
            vector<glm::vec3> translations = it->second.getTranslations(), rotations = it->second.getRotations();
            // are other rotation axis working ?
            for(unsigned int translationsIndex = 0; translationsIndex < translations.size(); translationsIndex++)
            {
                glm::vec3 translation = translations[translationsIndex];
                Vector3D vec = Vector3D(translation); // should add other rotation if important
                //print("vec: " + toString(vec));
                double d = distance(vecPos, vec); /// could at least compute only one time
                if(d > rangeToCheck) continue;
                vector<glm::vec3> vertices = it->second.m_glObject.m_vertices;
                if(d <= interactionRange + getMaxRadius(vertices))
                {
                    for(unsigned int verticesIndex = 0; verticesIndex < vertices.size(); verticesIndex += 4)
                    {
                        //print("Coordinates: " + toString(Vector3D(vertices[verticesIndex])));

                        double angle = rotations[translationsIndex][2];

                        Vector3D A = rotationAndTranslation(Vector3D(vertices[verticesIndex]), vec, angle/* + 180*/), // doesn't seem to make it perfect for all structures !
                                 B = rotationAndTranslation(Vector3D(vertices[verticesIndex + 1]), vec, angle/* + 180*/),
                                 C = rotationAndTranslation(Vector3D(vertices[verticesIndex + 2]), vec, angle/* + 180*/),
                                 D = rotationAndTranslation(Vector3D(vertices[verticesIndex + 3]), vec, angle/* + 180*/); /// !!!!!!!!!!!!!!!!!!! TODO: debug with 3DLine to see where ABCD are !!!!!!!!!!!!!!!!! /// SHOULD BE BETTER WITH GRAPHICAL DEBUG RECTANGLE

                        Vector3D interPt = isRectangleInTarget(A, B, C, D, descendingFromFoot, descending, vecPos); // need rotation
                        if(interPt.X != -1 || interPt.Y != -1 || interPt.Z != -1)
                        {
                            double dPrime = distance(interPt, vecPos); /// SHOULD USE CAMERA INSTEAD OF PLAYER FEET VECTOR3D
                            if(dPrime < minDistance)
                            {
                                //print("New d: " + convertNbToStr(dPrime));
                                minDistance = dPrime;
                                structureIdNearestTarget = it->first;
                                print(currentChkToCheck + " " + convertNbToStr(structureIdNearestTarget));
                                partIndex = verticesIndex / 4;
                                finalAngle = angle;
                                finalVec = vec;
                                //print("vec: " + toString(finalVec));
                                //print(convertNbToStr(minDistance) + " " + convertNbToStr(it->first) + " " + toString(A));
                                //print("BANG: " + toString(A) + " ! " + toString(Vector3D(vertices[verticesIndex])) + " ! " + toString(vec) + " ! " + convertNbToStr(rotations[translationsIndex][2]));

                                if(renderOutlineSelection)
                                {
                                    lineDebugToAdd.clear(); // could be optimized with a permanent sized array of 4 pairs

                                    coordinatesDebug = {A.X, A.Y, A.Z,
                                                        B.X, B.Y, B.Z,
                                                        C.X, C.Y, C.Z,
                                                        D.X, D.Y, D.Z};
                                }

                                /*if(structureIdNearestTarget == 175)
                                {
                                    print("verticesIndex: " + convertNbToStr(verticesIndex));
                                    print("translation: " + toString(translation));
                                    print("angle: " + convertNbToStr(angle));
                                    print("vertices: " + toString(vertices[verticesIndex]));
                                    print("finalCoordinates: " + toString(A) + " | " + toString(B) + " | " + toString(C) + " | " + toString(D));
                                }*/
                                /* used to be
                                p[0] = make_pair(A.X, A.Y);
                                p[1] = make_pair(B.X, B.Y);
                                p[2] = make_pair(C.X, C.Y);
                                p[3] = make_pair(D.X, D.Y);*/
                                /*lineDebugToAdd.push_back(make_pair(A.X, A.Y));
                                lineDebugToAdd.push_back(make_pair(B.X, B.Y));
                                lineDebugToAdd.push_back(make_pair(C.X, C.Y));
                                lineDebugToAdd.push_back(make_pair(D.X, D.Y));*/
                                //print("ALL POINTS ARE THE SAME ? " + convertNbToStr(lineDebugToAdd.size()) + " " + toString(A) + " ! " + toString(B) + " ! " + toString(C) + " ! " + toString(D)); /// YES SIR !
                                /*lineDebug.push_back(Line3D(A.X, A.Y));
                                lineDebug.push_back(Line3D(B.X, B.Y));
                                lineDebug.push_back(Line3D(C.X, C.Y));
                                lineDebug.push_back(Line3D(D.X, D.Y));*/
                                if(descending)
                                    return make_tuple(structureIdNearestTarget, partIndex, minDistance, coordinatesDebug, finalAngle, finalVec); // here doesn't bother which is the nearest because we just want to know if there is something under
                            }
                        }
                    }
                    //structures.push_back(make_tuple(it->first, vec, rotations[translationsIndex][2]));
                }
            }
        }
    }
    if(renderOutlineSelection)
    {
        if(minDistance != interactionRange && !descendingFromFoot)
        {
           // used to be
           // for(unsigned short i = 0; i < 4; i++)
                //lineDebugToAdd.push_back(p[i]);
           lineDebugToAdd.push_back(coordinatesDebug);
        }
    }
    /*for(unsigned int structuresIndex = 0; structuresIndex < structures.size(); structuresIndex++)
    {
        tuple<unsigned short, Vector3D, unsigned short> structure = structures[structuresIndex];
        get<1>(structure)
    }*/

    return make_tuple(structureIdNearestTarget, partIndex, minDistance, coordinatesDebug, finalAngle, finalVec);
}

tuple<unsigned short, short, unsigned short, vector<double>, unsigned short, Vector3D> getStructureIdTargeting(bool descendingFromFoot)
{
    Position pos = thePlayer->getViewGravity()->getGravityPosition();
    //tuple<unsigned short, unsigned short, unsigned short, vector<double>, unsigned short> t = getStructureIdTargetingPos(descendingFromFoot, pos.getX(), pos.getY(), pos.getZ() + eyeHeight);
    return getStructureIdTargetingPos(descendingFromFoot, pos.getX(), pos.getY(), pos.getZ() + eyeHeight)/*make_tuple(get<0>(t), get<1>(t), get<2>(t))*/;
}

void reloadStructure(unsigned short strucIdDbIndex)
{
    //print("a2");
    string strucFile = structuresFolder + convertNbToStr(strucIdDbIndex) + STRUCTURE_FILE_EXTENSION;
    //if(file_exists(strucFile))
    {
        //strucIdDbStruc.clear();
        //strucTranslations.clear();

    //print("a2.5");
        strucIdDbStruc[linkStrucVec[strucIdDbIndex]] = Structure(/*"Extensions\\LemnosLife\\Map\\Common\\Items\\peach.struc"*/strucFile); // could be optimized (like if no texture modification don't reload texture...) (for a full reload (cf initRender etc) 0.125s here spend 0.100s
    //print("a2.6");
        //vector<glm::vec3> tmp;
        //strucTranslations[strucIdDbIndex] = tmp;
    }
    //print("a3");
}

void loadObjects(string currentChunk)
{
    if(!configurationDataBool["initializeObjects"]) return;
    vector<string> chunkCoordinatesStr = split(currentChunk);
    unsigned short chunkCoordinates[2];
    for(unsigned short i = 0; i < 2; i++)
        chunkCoordinates[i] = convertStrToInt(chunkCoordinatesStr[i]);

    long chunkViewPlusOne = configurationDataLong["chunkView"] + 1;
    short chunkCoordinatesX = chunkCoordinates[0], chunkCoordinatesY = chunkCoordinates[1];

    //We look at all structures and load the new translations and rotations for each
    for(map<int, vector<glm::vec3>>::iterator it = strucTranslations.begin(); it != strucTranslations.end(); it++)
    {
        vector<glm::vec3> strucTranslationsTmp, strucRotationsTmp;

        for(short x = chunkCoordinatesX - chunkViewPlusOne; x <= chunkCoordinatesX + chunkViewPlusOne && x >= 0; x++)
        {
            for(short y = chunkCoordinatesY - chunkViewPlusOne; y <= chunkCoordinatesY + chunkViewPlusOne && y >= 0; y++)
            {
                vector<glm::vec3> translationsTmp = chunksLoaded[convertNbToStr(x) + " " + convertNbToStr(y)].getTranslations(it->first),
                                  rotationsTmp = chunksLoaded[convertNbToStr(x) + " " + convertNbToStr(y)].getRotations(it->first);
                strucTranslationsTmp.insert(strucTranslationsTmp.end(), translationsTmp.begin(), translationsTmp.end());
                //print(rotationsTmp.size());
                strucRotationsTmp.insert(strucRotationsTmp.end(), rotationsTmp.begin(), rotationsTmp.end());
                toInitLock.lock();
                strucTranslationsToInit[it->first] = true;
                //print("init");
                toInitLock.unlock();
            }
        }

        translationsLock.lock();
        strucTranslations[it->first] = strucTranslationsTmp;
        //print(convertNbToStr(strucRotationsTmp.size()));
        strucRotations[it->first] = strucRotationsTmp;
        translationsLock.unlock();
    }
}

bool itemRenderInitialized = false;

void initItemsRender()
{
    if(itemRenderInitialized)
        return;
    itemRenderInitialized = true;
    //print("initializing !");
    for(map<unsigned int, DynamicGl_object>::iterator it = items3D.begin(); it != items3D.end(); it++)
    {
        it->second.initializeRender();
        it->second.initialize();
    }
    //print("initialized !");
}

void initObjectsRender()
{
    //vector<glm::vec3> /*coo0, coo1,*/ coo2, rot;

    /*coo0.push_back(glm::vec3(3653.6, 13075.5, 12.52));
    coo1.push_back(glm::vec3(3653.6, 13075.5, 14.52));*/
    //coo2.push_back(glm::vec3(3653.6, 13075.5, 16.52));
    //rot.push_back(glm::vec3(0, 0, 0));

    //print("hallo");
    initItemsRender();
    //glm::vec3 rot = glm::vec3(0, 0, 0);

    unsigned int itemsOnGroundSize = itemsOnGround.size();
    for(unsigned int itemsOnGroundIndex = 0; itemsOnGroundIndex < itemsOnGroundSize; itemsOnGroundIndex++)
    {
        tuple<View, unsigned int, unsigned int> item = itemsOnGround[itemsOnGroundIndex];
        View view = get<0>(item);
        Position pos = /*get<0>(item)*/view.getPosition();
        ViewAngle viewAngle = view.getViewAngle();
        //addChatMessage("0: " + pos.toString());
        items3D[get<1>(item)].add(getVec3(pos), getVec3ViewAngle(viewAngle));
    }
    /*for(map<unsigned int, DynamicGl_object>::iterator it = items3D.begin(); it != items3D.end(); it++)
    {
        it->second.initializeRender();
        it->second.initialize();*/

        //glm::vec3 coo = glm::vec3(/*pos.getX(), pos.getY(), pos.getZ() + 1*/3653.6, 13075.5, 16.52), rot = glm::vec3(0, 0, 0);
        //it->second.add(coo, rot);

        //it->second.initializeTranslations(coo2, rot);
    //}

    /*glm::vec3 rot = glm::vec3(0, 0, 0); /// SURE TO NEED TO WAIT UNTIL HERE TO DO THIS ITEM STUFF ?

    unsigned int itemsOnGroundSize = itemsOnGround.size();
    for(unsigned int itemsOnGroundIndex = 0; itemsOnGroundIndex < itemsOnGroundSize; itemsOnGroundIndex++)
    {
        tuple<Position, unsigned int, unsigned int> item = itemsOnGround[itemsOnGroundIndex];
        Position pos = get<0>(item);
        items3D[get<1>(item)].add(getVec3(pos), rot);
    }*/

    /*for(map<unsigned int, Structure>::iterator it = items3DDbg0.begin(); it != items3DDbg0.end(); it++)
    {
        it->second.initializeRender();
        it->second.initializeTranslations(coo0, rot);
    }*/

    /*for(map<unsigned int, Gl_object>::iterator it = items3DDbg1.begin(); it != items3DDbg1.end(); it++)
    {
        it->second.initializeRender();
        it->second.initializeTranslations(coo1, rot);
    }*/

    if(!configurationDataBool["initializeObjectsRender"]) return;
    //strucIdDbStruc.clear();
    //strucTranslationsToInit.clear();
    for(map<int, vector<glm::vec3>>::iterator it = strucTranslations.begin(); it != strucTranslations.end(); it++) // could call initObjectRender with it->first no ?
    {
        strucIdDbStruc[linkStrucVec[it->first]].initializeRender();
        vector<glm::vec3> rotations = strucRotations[it->first];
        strucIdDbStruc[linkStrucVec[it->first]].initializeTranslations(it->second, rotations);
        strucTranslationsToInit[it->first] = false;
    }


    //print("init render object");
}

void initObjectRender(unsigned short id, bool force)
{
    // check "initializeObjectsRender" bool ?
    strucIdDbStruc[linkStrucVec[id]].initializeRender();
    vector<glm::vec3> rotations = strucRotations[id];
    strucIdDbStruc[linkStrucVec[id]].initializeTranslations(strucTranslations[id], rotations, force);
    strucTranslationsToInit[id] = false;
}

void renderObjects()
{
    //print("render object 0");
    if(configurationDataBool["objectsRender"])
    {
        //print("render object 1");
        for(map<int, vector<glm::vec3>>::iterator it = strucTranslations.begin(); it != strucTranslations.end(); it++)
        {
            //print("render object 2");
            int id = it->first;
            vector<glm::vec3> vec = it->second, rot = strucRotations[it->first];
            unsigned long vecSize = vec.size();

            toInitLock.lock();
            if(strucTranslationsToInit[id]) //If an initialisation is needed we update the structures
            {
                translationsLock.lock();
                strucIdDbStruc[linkStrucVec[id]].updateTranslations(vec, rot);
                strucTranslationsToInit[id] = false;
                translationsLock.unlock();
                //print("render object 3");
            }
            toInitLock.unlock();

            if(vecSize != 0)
            {
                strucIdDbStruc[linkStrucVec[id]].render();
                //print("render object 4");
            }
        }
    }
}
