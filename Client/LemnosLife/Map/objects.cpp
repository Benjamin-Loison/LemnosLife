#define GLEW_STATIC
#include <GL/glew.h>
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
#include "../../Vehicles/Vehicle.h"
#include "../../Network/Main/client.h"
#include "../../Guns/Engine/Gun.h"
#include "User/User.h"

using namespace std;

//Global variables TODO : make cleaner
vector<string> strucIdDbStr; // STRUC MAP ARMA SIZE
vector<bool> strucIdDbBool; // STRUC MAP ARMA SIZE
vector<short> linkStrucVec; // STRUC MAP ARMA SIZE // ça sert vraiment à quelque chose ce truc ?
vector<Structure> strucIdDbStruc; // STRUC MODELIZED SIZE

map<int, vector<glm::vec3>> strucTranslations, strucRotations;
map<int, bool> strucTranslationsToInit;

unsigned int itemsOnGroundAlready3D = 0;

bool itemRenderInitialized = false;

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
    vector<glm::vec3> tmp; // doesn't used to be outside the for loop
    for(unsigned short strucIdDbIndex = 0; strucIdDbIndex < strucIdDbStr.size(); strucIdDbIndex++)
    {
        string strucFile = structuresFolder + convertNbToStr(strucIdDbIndex) + STRUCTURE_FILE_EXTENSION;
        //print(convertNbToStr(strucIdDbIndex));
        ///if(doesFileExist(strucFile))
        {
            //print("Y " + convertNbToStr(strucIdDbStruc.size()));
            strucIdDbBool.push_back(true);
            linkStrucVec.push_back(strucIdDbStruc.size());
            strucIdDbStruc.push_back(Structure(strucFile));
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

bool isAnATM(unsigned short structureId) // not used
{
    return structureId == ID_ATM_COVERED || structureId == ID_ATM_NOT_COVERED;
}

bool lookingAnATM(unsigned short targetId, unsigned short targetSubId)
{
    return (targetId == ID_ATM_COVERED && targetSubId == 11) || (targetId == ID_ATM_NOT_COVERED && targetSubId == 11); // have to be changed when model will changed
}

#define MAX_STRUCTURE_HYPOTENUSE_3D 48.58
#define MAX_STRUCTURE_HYPOTENUSE_2D 22.85
/// 3D: 623 48.5721
/// 2D: maxD: 474 22.8474
// bridge is already a case in point: 21 * sqrt(2) = 29.7
/// SHOULD BE 3D HYPOTENUSE ?
// used to be (new) 10
// used to be 50
// should save this constant in a file
#define RANGE_TO_CHECK_3D (INTERACTION_RANGE_3D + MAX_STRUCTURE_HYPOTENUSE_3D)
#define RANGE_TO_CHECK_2D (INTERACTION_RANGE_2D + MAX_STRUCTURE_HYPOTENUSE_2D)
/// RANGE_TO_CHECK_2D isn't well computed for getGounrdAltitudeWithStructure etc
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

    ///print("rot: " + toString(vec) + " " + toString(middle) + " " + convertNbToStr(angle) + " " + toString(vec));
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

double getMaxRadius(vector<glm::vec4> vertices)
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

double getMaxRadius(vector<glm::vec4>* vertices)
{
    double maxRadius = 0;
    for(unsigned int verticesIndex = 0; verticesIndex < vertices->size(); verticesIndex++)
    {
        double radius = Vector3D(vertices->at(verticesIndex)).length();
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

void addIfNotIn(Vector2D el, vector<Vector2D>* vec)
{
    unsigned int vecSize = vec->size();
    for(unsigned int vecIndex = 0; vecIndex < vecSize; vecIndex++)
    {
        Vector2D in = vec->at(vecIndex);
        if(el == in)
            return;
    }
    vec->push_back(el);
}

// is target relative or absolute ?
tuple<unsigned short, short, double/*unsigned short*/, vector<double>, unsigned short, Vector3D> getStructureIdTargetingPos(bool descendingFromFoot, double x, double y, double z, bool descending, bool horizontal, Vector3D target, OBB* obb, bool drawRed) // return nearest structure in target // not well manage if exactly on multiple chunks ?
{ /// for x y z could also work with a vector<double> but seems to be too much syntax heavy - used to be double, double, double
    // INTERACTION_RANGE value 8
    /// WILL CHECK DISTANCE TO ALL STRUCTURES IN CURRENT CHUNK
    // CHECK 1 square range chunk around (1000m)

    vector<string> chkToCheck;
    chkToCheck.push_back(getChunkName(x, y));

    double rangeToCheck = descending ? RANGE_TO_CHECK_2D : RANGE_TO_CHECK_3D;

    if(descendingFromFoot)
    {
        rangeToCheck = MAX_STRUCTURE_HYPOTENUSE_2D;
    }

    double relativeX = remainderEuclidianDivision(x, get<DOUBLE>(mapData)["chunkSize"]); // MANAGE LEFT AND RIGHT CHUNKS // chunkGroundSize is 1000 meters, used to be chunkGroundSize everywhere instead of chunkSize
    bool left = false, right = false, up = false, down = false;

    #define xMinusChunkSize x - get<DOUBLE>(mapData)["chunkSize"]
    #define xPlusChunkSize x + get<DOUBLE>(mapData)["chunkSize"]

    #define yMinusChunkSize y - get<DOUBLE>(mapData)["chunkSize"]
    #define yPlusChunkSize y + get<DOUBLE>(mapData)["chunkSize"]
    // are these macros so useful ?

    if(relativeX <= rangeToCheck)
    {
        //addChatMessage("left");
        left = true;
        chkToCheck.push_back(getChunkName(xMinusChunkSize, y));
    }
    else if(relativeX >= get<DOUBLE>(mapData)["chunkSize"] - rangeToCheck)
    {
        //addChatMessage("right");
        right = true;
        chkToCheck.push_back(getChunkName(xPlusChunkSize, y));
    }

    double relativeY = remainderEuclidianDivision(y, get<DOUBLE>(mapData)["chunkSize"]); // MANAGE UP AND DOWN CHUNKS // used to be x instead of y lel
    //addChatMessage(convertNbToStr(relativeY) + " " + convertNbToStr(rangeToCheck));
    if(relativeY <= rangeToCheck)
    {
        //addChatMessage("down");
        down = true; // is inversed ?
        chkToCheck.push_back(getChunkName(x, yMinusChunkSize));
    }
    else if(relativeY >= get<DOUBLE>(mapData)["chunkSize"] - rangeToCheck)
    {
        //addChatMessage("up");
        up = true;
        chkToCheck.push_back(getChunkName(x, y + get<DOUBLE>(mapData)["chunkSize"]));
    }

    // MANAGE DIAGONALS CHUNKS

    if(left)
    {
        if(up)
        {
            chkToCheck.push_back(getChunkName(xMinusChunkSize, yPlusChunkSize));
        }
        else if(down)
        {
            chkToCheck.push_back(getChunkName(xMinusChunkSize, yMinusChunkSize));
        }
    }
    else if(right) // both left and right shouldn't be able to be on true at the same time
    {
        if(up)
        {
            chkToCheck.push_back(getChunkName(xPlusChunkSize, yPlusChunkSize));
        }
        else if(down)
        {
            chkToCheck.push_back(getChunkName(xPlusChunkSize, yMinusChunkSize));
        }
    }
    //chkToCheck.push_back(getChunkName(left ? xPlusChunkSize : xMinusChunkSize, up ? yPlusChunkSize : yMinusChunkSize)); // doesn't used to be ternary and takes a lot of lines but are needed because it is else if and not else lol


    //vector<tuple<unsigned short, Vector3D, unsigned short>> structures;
    // generate parts of structures in real time or generate them at startup (first option here)
    double interactionRange = INTERACTION_RANGE_3D;///, rangeToCheck = RANGE_TO_CHECK;
    if(descendingFromFoot)
    {
        // if ppow(10, 1) bug for big structures like basketball playground
        interactionRange = MAX_STRUCTURE_HYPOTENUSE_2D;//pow(10, 2); /// should make kind of cube root
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
        Chunk* chk = &chunksLoaded[currentChkToCheck]; // doesn't used to be a pointer lol - may crash now ?
        for(map<unsigned int, Structure>::iterator it = chk->m_structures.begin(); it != chk->m_structures.end(); it++) // why structure "propre" to a chunk ? (42)
        {
            unsigned int structureId = it->first;
            //print("s: " + convertNbToStr(structureId));
            vector<glm::vec3>* translations = it->second.getTranslationsPtr(), *rotations = it->second.getRotationsPtr(); // doesn't used to be pointers
            // are other rotation axis working ?
            for(unsigned int translationsIndex = 0; translationsIndex < translations->size(); translationsIndex++)
            {
                glm::vec3 translation = translations->at(translationsIndex);
                Vector3D vec = Vector3D(translation); // should add other rotation if important
                //print("vec: " + toString(vec));
                double d = distance(vecPos, vec); /// could at least compute only one time
                if(d > rangeToCheck) continue;
                vector<glm::vec4>* vertices = &it->second.m_glObject.m_vertices; // doesn't used to be a pointer
                if(d <= interactionRange + getMaxRadius(vertices))
                {
                    for(unsigned int verticesIndex = 0; verticesIndex < vertices->size(); verticesIndex += 4)
                    {
                        //print("Coordinates: " + toString(Vector3D(vertices[verticesIndex])));

                        double angle = rotations->at(translationsIndex)[2];

                        Vector3D A = rotationAndTranslation(Vector3D(vertices->at(verticesIndex)), vec, angle/* + 180*/), // doesn't seem to make it perfect for all structures !
                                 B = rotationAndTranslation(Vector3D(vertices->at(verticesIndex + 1)), vec, angle/* + 180*/),
                                 C = rotationAndTranslation(Vector3D(vertices->at(verticesIndex + 2)), vec, angle/* + 180*/),
                                 D = rotationAndTranslation(Vector3D(vertices->at(verticesIndex + 3)), vec, angle/* + 180*/); /// !!!!!!!!!!!!!!!!!!! TODO: debug with 3DLine to see where ABCD are !!!!!!!!!!!!!!!!! /// SHOULD BE BETTER WITH GRAPHICAL DEBUG RECTANGLE

                        if(obb != nullptr)
                        {
                            double minZ = min(min(min(A.Z, B.Z), C.Z), D.Z), maxZ = max(max(max(A.Z, B.Z), C.Z), D.Z); // mhh bien dégueu comme modèle
                            if(minZ - BODY_HEIGHT <= z && z <= maxZ/* + BODY_HEIGHT*/ && maxZ >= z + 0.5) // bodyHeight ? somewhere
                            {
                                bool horizontalPart = false;
                                vector<Vector2D> vec;
                                /*vec.push_back(Vector2D(A));
                                vec.push_back(Vector2D(B));
                                vec.push_back(Vector2D(C));
                                vec.push_back(Vector2D(D));*/
                                Vector2D A2 = Vector2D(A), B2 = Vector2D(B), C2 = Vector2D(C), D2 = Vector2D(D);
                                addIfNotIn(A2, &vec);
                                addIfNotIn(B2, &vec);
                                addIfNotIn(C2, &vec);
                                addIfNotIn(D2, &vec);

                                //if(A == B)
                                /*

                                A B C D
                                X X
                                X   X
                                X     X
                                  X X
                                  X   X
                                    X X

                                */
                                if(vec.size() == 2) // could manage == 3 and == 4 if don't "close" the OBB
                                {
                                    OBB triangleOBB;
                                    triangleOBB.A = {A2.X, A2.Y};
                                    triangleOBB.B = {B2.X, B2.Y};
                                    triangleOBB.C = {C2.X, C2.Y};
                                    triangleOBB.D = {D2.X, D2.Y};

                                    if(isCollided(*obb, triangleOBB)) // should also do a temporary continuous model
                                    {
                                        return make_tuple(0, structureId/*0*/, 0, coordinatesDebug, 0, Vector3D());
                                    }
                                }
                            }
                        }
                        else
                        {
                            Vector3D interPt;
                            if(horizontal)
                            {
                                semiLineQuadrilateralIntersect(vecPos, target, A, B, C, D, &interPt); // second argument uses absolute coordinates
                            }
                            else
                            {
                                interPt = isRectangleInTarget(A, B, C, D, descendingFromFoot, descending, vecPos); // need rotation
                            }
                            bool isCollided = interPt.X != -1 || interPt.Y != -1 || interPt.Z != -1;
                            if(isCollided)
                            {
                                double dPrime = distance(interPt, vecPos); /// SHOULD USE CAMERA INSTEAD OF PLAYER FEET VECTOR3D
                                if(dPrime < minDistance)
                                {
                                    //print("New d: " + convertNbToStr(dPrime));
                                    minDistance = dPrime;
                                    structureIdNearestTarget = structureId;
                                    //print(currentChkToCheck + " " + convertNbToStr(structureIdNearestTarget));
                                    partIndex = verticesIndex / 4;
                                    finalAngle = angle;
                                    finalVec = vec;
                                    //print("vec: " + toString(finalVec));
                                    //print(convertNbToStr(minDistance) + " " + convertNbToStr(it->first) + " " + toString(A));
                                    //print("BANG: " + toString(A) + " ! " + toString(Vector3D(vertices[verticesIndex])) + " ! " + toString(vec) + " ! " + convertNbToStr(rotations[translationsIndex][2]));

                                    if(drawRed && renderOutlineSelection)
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
                                    /// TODO: should put back a boolean parameter to be able to use this for map binary structure or not for instance
                                    ///if(descending) // used to use this to return first found but problem when altitude is important for multiple layers stairs
                                    ///    return make_tuple(structureIdNearestTarget, partIndex, minDistance, coordinatesDebug, finalAngle, finalVec); // here doesn't bother which is the nearest because we just want to know if there is something under
                                }
                            }
                            /*if(collisionRaytracing) // copied from server, works fine if use to_string in toString(Vector3D) otherwise will be nearly perfect
                            {
                                string color = isCollided ? "0,1,0,1" : "1,0,0,1";
                                sendLocal("DebugLines " + toString(A, ",") + " " + toString(B, ",") + " " + color);
                                sendLocal("DebugLines " + toString(B, ",") + " " + toString(C, ",") + " " + color);
                                sendLocal("DebugLines " + toString(C, ",") + " " + toString(D, ",") + " " + color);
                                sendLocal("DebugLines " + toString(D, ",") + " " + toString(A, ",") + " " + color);
                            }*/
                        }
                    }
                    //structures.push_back(make_tuple(it->first, vec, rotations[translationsIndex][2]));
                }
            }
        }
    }
    if(drawRed && renderOutlineSelection)
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

tuple<unsigned short, short, /*unsigned short*/double, vector<double>, unsigned short, Vector3D> getStructureIdTargeting(bool descendingFromFoot, bool drawRed)
{
    Position pos = thePlayer->getViewGravity()->getGravityPosition();
    //tuple<unsigned short, unsigned short, unsigned short, vector<double>, unsigned short> t = getStructureIdTargetingPos(descendingFromFoot, pos.getX(), pos.getY(), pos.getZ() + m_eyeHeight);
    return getStructureIdTargetingPos(descendingFromFoot, pos.getX(), pos.getY(), pos.getZ() + thePlayer->m_eyeHeight, false, false, Vector3D(), nullptr, drawRed)/*make_tuple(get<0>(t), get<1>(t), get<2>(t))*/; // used to be everywhere m_eyeHeight instead of getEyeHeight() (before animations)
}
