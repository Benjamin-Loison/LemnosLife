#include "Vehicle.h"
#include "../LemnosLife/Main/main.h"
#include "../LemnosLife/Render/Engine/textureManager.h"
#include "../LemnosLife/Render/Gui/Gui/GuiChat.h"
#include "../LemnosLife/Map/map.h"
#include "../LemnosLife/Map/mapUtils.h"
#include "../LemnosLife/Map/User/User.h"
#include "../FilePlus/file_plus.h"
#include "../StringPlus/string_plus.h"
#include "../Logger/logger.h"
#include "../FilePlus/configuration.h"
#include <map>
using namespace std;

map<unsigned int, Vehicle> vehicles;
unsigned int availableId = 0;
string vehiclesSkins, vehiclesModels;

void initializeVehicles()
{
    vehiclesSkins = picturesFolder + "Vehicles" + pathSeparatorStr;
    vehiclesModels = commonMapFolder + "Vehicles" + pathSeparatorStr;
}

Vehicle::Vehicle() {} // why required ?

Vehicle::Vehicle(string vehicleName, ViewGravity viewGravity, string camouflage) : m_name(vehicleName), m_viewGravity(viewGravity), m_camouflage(camouflage), m_needInit(true), m_lastPosition(viewGravity.getGravityPosition())
{
    availableId++;
}

void addVehicle(string vehicleName, ViewGravity viewGravity, string camouflage)
{
    vehicles[availableId] = Vehicle(vehicleName, viewGravity, camouflage);
}

void Vehicle::initializeVehicle()
{
    initializeTexture();
    initializeRender();
}

void Vehicle::initializeTexture()
{
    m_texture = addGetTexture(string(vehiclesSkins + m_name + m_camouflage + ".png"), "loadSkinTexture");
    m_refreshSkinFinished = true;
}

void Vehicle::initializeRender() // considering all vehicles with different texture because of the future presence of many camouflage paints
{
    string vehiclePath = vehiclesModels + m_name, vehicleFilePath = vehiclePath + STRUCTURE_FILE_EXTENSION;
    vector<string> lines = getFileContent(vehiclePath + ".txt");
    for(unsigned int i = 0; i < lines.size(); i++) /// should make a more precise model for collisions
    {
        string line = lines[i];
        vector<string> lineParts = split(line);
        unsigned short linePartsSize = lineParts.size();
        if(linePartsSize > 0)
        {
            if(lineParts[0] == "collisions")
            {
                if(linePartsSize > 4)
                {
                    for(unsigned short i = 1; i < 5; i++)
                    {
                        string coordinates = lineParts[i];
                        vector<string> coordinatesParts = split(coordinates, ";");
                        unsigned short coordinatesPartsSize = coordinatesParts.size();
                        if(coordinatesPartsSize > 2)
                        {
                            // TODO: check type
                            //print("hello my world !");
                            double x = convertStrToDouble(coordinatesParts[0]), y = convertStrToDouble(coordinatesParts[1]); // could use z (cf 080320-1217)
                            m_collisions[i - 1] = point({x, y});
                        }
                    }
                }
            }
        }
    }
    //print("Vehicle file: " + vehicleFilePath);
    lines = getFileContent(vehicleFilePath);

    unsigned int linesSize = lines.size(), realLines = 0;
    //print("Vehicle size: " + convertNbToStr(linesSize));
    for(unsigned int i = 0; i < linesSize; i++) /// copied from Structures.cpp
    {
        if(i == 0 || lines[i][0] != '/') realLines++;
    }

    texNumber = realLines * 3 * 2 * 2; /// TODO: should be executed once, why in users initialize Users with coordinates of the player is specifiec each time ? and not just for game launch ?
    verticesNumber = realLines * 3 * 3 * 2; /// last * 2 for patch cf FOLLOWING TODO
    float vertices[verticesNumber], texCoord[texNumber];
    unsigned int texIndex = 0, vertexIndex = 0;
    for(unsigned int i = 0; i < linesSize; i++)
    {
        string line = lines[i];
        if(i == 0 || line[0] == '/') continue;
        vector<string> inf = split(line);
        /*for(unsigned short i = 0; i < 2; i++)
        {
            for(unsigned short x = 0; x < 4; x++)
            {
                vector<string> texVector = split(inf[2 + x], ";");
                for(unsigned short y = 0; y < 2; y++)
                {
                    texCoord[texIndex] = convertStrToDouble(texVector[y]); // could make index product but seems slower
                    texIndex++;
                }
            }
        }*/
        vector<double> texTmp;
        for(unsigned short x = 0; x < 4; x++) /// TODO: do like Structures ? but how to manage rotation ? so here need king of adapter to make quadrilateral two triangles and don't manage texture for the moment
        {
            vector<string> texVector = split(inf[2 + x], ";");
            for(unsigned short y = 0; y < 2; y++)
            {
                texTmp.push_back(convertStrToDouble(texVector[y]));
            }
        }
        for(unsigned short v = 0; v < 2 * 3; v++)
        {
            texCoord[texIndex] = texTmp[v];
            texIndex++;
        }

        for(unsigned short v = 0; v < 2; v++)
        {
            texCoord[texIndex] = texTmp[v];
            texIndex++;
        }
        for(unsigned short v = 2 * 2; v < 2 * 4; v++)
        {
            texCoord[texIndex] = texTmp[v];
            texIndex++;
        }

        vector<double> verticesTmp;
        for(unsigned short x = 0; x < 4; x++) /// TODO: do like Structures ? but how to manage rotation ? so here need king of adapter to make quadrilateral two triangles and don't manage texture for the moment
        {
            vector<string> vertexVector = split(inf[6 + x], ";");
            for(unsigned short y = 0; y < 3; y++)
            {
                //vertices[vertexIndex] = convertStrToDouble(vertexVector[y]);
                verticesTmp.push_back(convertStrToDouble(vertexVector[y]));
            }
        }
        for(unsigned short v = 0; v < 3 * 3; v++)
        {
            vertices[vertexIndex] = verticesTmp[v];
            vertexIndex++;
        }

        for(unsigned short v = 0; v < 3; v++)
        {
            vertices[vertexIndex] = verticesTmp[v];
            vertexIndex++;
        }
        for(unsigned short v = 3 * 2; v < 3 * 4; v++)
        {
            vertices[vertexIndex] = verticesTmp[v];
            vertexIndex++;
        }

        //vertexIndex += 3 * 3 * 2; /// 18
        //print(convertNbToStr(vertexIndex) + " / " + convertNbToStr(realLines * 4 * 3) + " | " + convertNbToStr(texIndex) + " / " + convertNbToStr(realLines * 4 * 2)); /// WHY OUT BOUNDARIES ?!
    }
    // TODO: could share code with user ?

    shader = Shader("shader1.vs", "shader1.fs"); // shouldn't be ran once and then use a global variable ?

    //Init VBO and VAO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texCoord), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texCoord), texCoord);

    //Send data to VAO
    glBindVertexArray(m_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, ((char*)NULL + (sizeof(vertices))));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec3 getVec3(ViewGravity* viewGravity) // seems useless
{
    return getVec3(viewGravity->getGravityPosition());
}

point getPoint(Position pos) // horrible with functions in vector3d to activate (includes suck)
{
    return {pos.getX(), pos.getY()};
}

point sumPoint(point pt0, point pt1)
{
    return point({pt0.x + pt1.x, pt0.y + pt1.y});
}

glm::vec3 getVec3(Position pos)
{
    double x = pos.getX(), y = pos.getY(), z = pos.getZ();
    return glm::vec3(x, y, z);
}

glm::vec3 getVec3(Vector3D vec) // shouldn't be here
{
    return glm::vec3(vec.X, vec.Y, vec.Z);
}

glm::vec3 getVec3ViewAngle(ViewAngle viewAngle)
{
    double x = 0, y = 0, z = viewAngle.getPhi(); // TODO: how to deal with theta ?
    return glm::vec3(x, y, z);
}

void Vehicle::render()
{
    if(m_needInit)
        initializeTexture();
    if(m_refreshSkinFinished)
        initializeRender();
    if(m_refreshSkinFinished)
    {
        Position pos = m_viewGravity.getGravityPosition();
        ViewGravity* viewGravity = thePlayer->getViewGravity();
        double x = pos.getX(), y = pos.getY(), z = pos.getZ(), angle = viewGravity->getViewAngle().getPhi();

        shader.use();

        glBindTexture(GL_TEXTURE_2D, m_texture);

        glBindVertexArray(m_VAO);

        glm::mat4 modelview = getModelview();
        GravityPosition gP = viewGravity->getGravityPosition();
        //double seaHeight = get<DOUBLE>(mapData)["seaHeight"]; // just to patch compilation bug // why DOUBLE no more well defined ? - patched (just needed include configuration.h)
        gP.setZ(0.05    /*get<DOUBLE>(mapData)["seaHeight"]*/);
        viewGravity->updatePosition(gP);
        Position newPos = viewGravity->getGravityPosition();
        if(newPos != m_lastPosition || angle != m_lastAngle)
        {
            for(unsigned short i = 0; i < 4; i++)
            {
                point ptRot = getPoint(newPos);
                point pt = sumPoint(ptRot, rotate(m_collisions[i], point({0, 0}), angle));
                double altitude = getGroundAltitude/*WithStructure*/(pt.x, pt.y/*, 10*/); // TODO: should consider structures !
                //addChatMessage(toString(m_collisions[i]) + " | " + toString(pt) + " | " + convertNbToStr(altitude));
                bool isCollision = altitude >= 0; // could make faster if return directly on first collision found for altitude, let's firstly only manage 2D collisions (080320-1217)
                if(isCollision)
                {
                    newPos = m_lastPosition;
                    angle = m_lastAngle;
                    //addChatMessage("Hum j'adore quand ça touche !"); // :') tired 08/03/20 00:07 AM
                    break;
                }
            }
        }
        m_lastPosition = newPos;
        m_lastAngle = angle;
        glm::vec3 vec = getVec3(newPos);
        modelview = glm::translate(modelview, vec/*glm::vec3(x, y, z)*/);
        modelview = glm::rotate(modelview, (float)glm::radians(/*m_viewGravity.getViewAngle().getPhi()*/angle/* + 90*/), glm::vec3(0, 0, 1));
        glm::mat4 modelviewProjection = getProjection() * modelview;
        shader.setMat4("modelviewProjection", modelviewProjection);
        glDrawArrays(GL_TRIANGLES, 0, verticesNumber); ///

        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void renderVehicles()
{
    for(map<unsigned int, Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
    {
        it->second.render();
    }
}
