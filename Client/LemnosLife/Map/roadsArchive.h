/*

ROADS WITHOUT BEING REALLY APPLIED TO GROUND USED TO BE:

#include <map>
#include <vector>
#include "GroundGl_object.h"
#include "../../FilePlus/file_plus.h"
#include "../../StringPlus/string_plus.h"
#include "../../Logger/logger.h"
#include "../../MathPlus/math_plus.h"
#include "../Main/main.h"
#include "map.h"
#include "mapUtils.h"
#include "roads.h"
#include "../../2D/vector2d.h"
using namespace std;

string roadsNames[ROADS_NUMBER] = {"tarmac_highway", "tarmac_main_road", "dirt_road", "concrete_city_road", "dirt_path"}; // TODO: could reorganize id by importance order
string roadsEndNames[ROADS_NUMBER] = {"tarmac_highway_end", "tarmac_main_road_end", "dirt_road_end", "concrete_city_road_end", "dirt_path_end"};
unsigned short roadsSizes[ROADS_NUMBER] = {14, 10, 10, 10, 7};
double roadsHeights[ROADS_NUMBER] = {0.01, 0.006, 0.004, 0.008, 0.002};
map<string, vector<unsigned short>> roadsChunks;
map<unsigned short, unsigned short> roadsType;
map<unsigned short, vector<double>> roadsChunksCoordinates; // one element for each coordinate (2n) first element of vector is the type
map<unsigned short, GroundGl_object> roadsGlObjects; // key: roadsType, value: roadsTypeGlObject
map<unsigned short, GroundGl_object> roadsEndGlObjects; // key: roadsType, value: roadsTypeGlObject
vector<unsigned short> roadsToRender;
unsigned short roadsNumber;

point getPositionRoad(unsigned short, double, bool = false);

double roadLength(unsigned short roadId)
{
    //print("roadLength - begin");
    if(roadsChunksCoordinates.find(roadId) == roadsChunksCoordinates.end()) return 0;
    vector<double> roadsCoordinates = roadsChunksCoordinates[roadId];
    double sum = 0;
    for(unsigned int roadsCoordinatesIndex = 0; roadsCoordinatesIndex < roadsCoordinates.size() - 3; roadsCoordinatesIndex++)
    {
        double x0 = roadsCoordinates[roadsCoordinatesIndex], y0 = roadsCoordinates[roadsCoordinatesIndex + 1], x1 = roadsCoordinates[roadsCoordinatesIndex + 2], y1 = roadsCoordinates[roadsCoordinatesIndex + 3];
        sum += distance(x0, y0, x1, y1);
    }
    //print("roadLength - end");
    return sum;
}

void initializeRoads() {} /// TODO: only load required chunks

void loadRoads(bool live)
{
    //print("loadRoads - begin");
    vector<string> roadsLines = getFileContent(roadsFolder + "roads.txt", live);
    for(unsigned int roadsLinesIndex = 0; roadsLinesIndex < roadsLines.size(); roadsLinesIndex++)
    {
        string roadsLine = roadsLines[roadsLinesIndex];
        vector<string> roadsLineParts = split(roadsLine, "@");
        string roadsLineParts0 = roadsLineParts[0];
        roadsType[roadsLinesIndex] = convertStrToInt(roadsLineParts[1]);
        vector<string> roadsLineParts0Parts = split(roadsLineParts0);
        vector<double> roadsChunkCoordinates;
        for(unsigned int roadsLineParts0PartsIndex = 0; roadsLineParts0PartsIndex < roadsLineParts0Parts.size(); roadsLineParts0PartsIndex++)
        {
            string roadsLineParts0PartsCouple = roadsLineParts0Parts[roadsLineParts0PartsIndex];
            vector<string> roadsLineParts0PartsCoupleCoordinates = split(roadsLineParts0PartsCouple, ",");
            roadsChunkCoordinates.push_back(convertStrToDouble(roadsLineParts0PartsCoupleCoordinates[0]));
            roadsChunkCoordinates.push_back(convertStrToDouble(roadsLineParts0PartsCoupleCoordinates[1]));
        }
        roadsChunksCoordinates[roadsLinesIndex] = roadsChunkCoordinates;
    }

    roadsLines = getFileContent(roadsFolder + "roadsChunks.txt", live);
    string chunkName;
    roadsNumber = roadsLines.size();
    for(unsigned int roadsLinesIndex = 0; roadsLinesIndex < roadsNumber; roadsLinesIndex++)
    {
        string roadsLine = roadsLines[roadsLinesIndex];
        vector<string> roadsLineParts = split(roadsLine);
        if(roadsLineParts.size() == 2)
        {
            chunkName = roadsLine;
        }
        else
        {
            vector<unsigned short> roadsChunk = roadsChunks[chunkName];
            roadsChunk.push_back(convertStrToInt(roadsLine));
            roadsChunks[chunkName] = roadsChunk;
        }
    }

    for(unsigned int roadsIndex = 0; roadsIndex < ROADS_NUMBER; roadsIndex++)
    {
        //print(convertNbToStr(roadsIndex) + " " + convertNbToStr(roadsSizes[roadsIndex]));
        roadsGlObjects[roadsIndex] = GroundGl_object(picturesMapRoadsFolder + roadsNames[roadsIndex] + ".png", false);
        roadsEndGlObjects[roadsIndex] = GroundGl_object(picturesMapRoadsFolder + roadsEndNames[roadsIndex] + ".png", false);
    }

    /* TEST confirmed: double tex[4][2] = {{1, 0}, {1, 1}, {0, 1}, {0, 0}},
           vertex[4][3] = {{15000, 16000, 50},
                           {15000, 15000, 50},
                           {16000, 15000, 50},
                           {16000, 16000, 50}};
    roadsGlObjects[0].addPart(tex, vertex);*/

    /*

We consider the road as follow:

#########|######|######
#        |      |
# ## ## #|# ## #|# ## # ...
#        |      |
#########|######|######

    *//*

    double tex[4][2] = {{1, 0}, {1, 1}, {0, 1}, {0, 0}};
    for(unsigned int roadsIndex = 0; roadsIndex < roadsNumber; roadsIndex++)
    {
       // print("Working on road: " + convertNbToStr(roadsIndex) + " " + convertNbToStr(roadLength(roadsIndex)) + " " + convertNbToStr(2 * roadsSizes[roadsIndex]));

        if(roadLength(roadsIndex) <= 2 * roadsSizes[roadsType[roadsIndex]]) continue; /// DO NOT FORGET CAS PARTICULIER (peut avoir 3 points, cf code LengthRoadsLL Java) !

        //print("Confirmed");
        vector<double> road = roadsChunksCoordinates[roadsIndex];
        double roadSize = roadsSizes[roadsType[roadsIndex]];
        line oldBottom, oldTop;
        for(unsigned int roadIndex = 0; roadIndex < road.size() - 2; roadIndex += 2)
        {
            point leftPoint{road[roadIndex], road[roadIndex + 1]}, rightPoint{road[roadIndex + 2], road[roadIndex + 3]}, middlePoint = getMiddle(leftPoint, rightPoint), topLeftPoint = rotate(middlePoint, leftPoint),
                  bottomLeftPoint = rotate(middlePoint, leftPoint, OPPOSITE_PI_DIVIDED_BY_2), topRightPoint = rotate(middlePoint, rightPoint, OPPOSITE_PI_DIVIDED_BY_2), bottomRightPoint = rotate(middlePoint, rightPoint);

            double vectorXLeftTopLeft = topLeftPoint.x - leftPoint.x, vectorYLeftTopLeft = topLeftPoint.y - leftPoint.y, distanceLeftTopLeft = distance(leftPoint, topLeftPoint), distanceSide = distance(leftPoint, rightPoint);
            vectorXLeftTopLeft /= distanceLeftTopLeft;
            vectorYLeftTopLeft /= distanceLeftTopLeft;

            //print("THAT: " + convertNbToStr(Vector2D(vectorXLeftTopLeft, vectorYLeftTopLeft).length()));
            topLeftPoint.x = leftPoint.x + vectorXLeftTopLeft * roadSize;
            topLeftPoint.y = leftPoint.y + vectorYLeftTopLeft * roadSize;
            //topLeftPoint = resize(topLeftPoint, roadSize);

            /* doesn't work

                topLeftPoint.x = vectorXLeftTopLeft * roadSize;
                topLeftPoint.y = vectorYLeftTopLeft * roadSize;
                topLeftPoint = resize(topLeftPoint, roadSize);
                topLeftPoint.x += leftPoint.x;
                topLeftPoint.y += leftPoint.y;

            *//*

            bottomLeftPoint.x = leftPoint.x - vectorXLeftTopLeft * roadSize;
            bottomLeftPoint.y = leftPoint.y - vectorYLeftTopLeft * roadSize;
            //topLeftPoint = resize(topLeftPoint, roadSize);

            double vectorXRightTopRight = topRightPoint.x - rightPoint.x, vectorYRightTopRight = topRightPoint.y - rightPoint.y, distanceRightTopRight = distance(rightPoint, topRightPoint);
            vectorXRightTopRight /= distanceRightTopRight;
            vectorYRightTopRight /= distanceRightTopRight;
            topRightPoint.x = rightPoint.x + vectorXRightTopRight * roadSize;
            topRightPoint.y = rightPoint.y + vectorYRightTopRight * roadSize;
            bottomRightPoint.x = rightPoint.x - vectorXRightTopRight * roadSize;
            bottomRightPoint.y = rightPoint.y - vectorYRightTopRight * roadSize;

            /*if(roadIndex < road.size() - 4)
            {
                leftPoint = point{road[roadIndex + 2], road[roadIndex + 3]};
                rightPoint = point{road[roadIndex + 4], road[roadIndex + 5]};
                middlePoint = getMiddle(leftPoint, rightPoint);
                point topRightRightPoint = rotate(middlePoint, rightPoint, OPPOSITE_PI_DIVIDED_BY_2), bottomRightRightPoint = rotate(middlePoint, rightPoint);

                double vectorXRightTopRight = topRightRightPoint.x - rightPoint.x, vectorYRightTopRight = topRightRightPoint.y - rightPoint.y, distanceRightTopRight = distance(rightPoint, topRightRightPoint);
                vectorXRightTopRight /= distanceRightTopRight;
                vectorYRightTopRight /= distanceRightTopRight;
                topRightRightPoint.x = rightPoint.x + vectorXRightTopRight * roadSize;
                topRightRightPoint.y = rightPoint.y + vectorYRightTopRight * roadSize;
                bottomRightRightPoint.x = rightPoint.x - vectorXRightTopRight * roadSize;
                bottomRightRightPoint.y = rightPoint.y - vectorYRightTopRight * roadSize;

                topRightPoint = reverse(getIntersection(getLine(topLeftPoint, topRightPoint), getLine(topRightPoint, topRightRightPoint)));
                bottomRightPoint = reverse(getIntersection(getLine(bottomLeftPoint, bottomRightPoint), getLine(bottomRightPoint, bottomRightRightPoint)));
            }*//*

            //print(convertNbToStr(roadIndex));
            point oldBottomLeftPoint = bottomLeftPoint, oldTopLeftPoint = topLeftPoint;
            line currentBottom = getLine(bottomLeftPoint, bottomRightPoint), currentTop = getLine(topLeftPoint, topRightPoint);
            if(roadIndex > 1)
            {
                bottomLeftPoint = reverse(getIntersection(oldBottom, currentBottom));
                topLeftPoint = reverse(getIntersection(oldTop, currentTop));

                double roadRepeatsBottom = Vector2D(getVector2D(oldBottomLeftPoint), getVector2D(bottomLeftPoint)).length() / roadSize,
                   roadRepeatsTop = Vector2D(getVector2D(oldTopLeftPoint), getVector2D(topLeftPoint)).length() / roadSize;

                // LEFT

                //tex[0][1] = -roadRepeatsTop;
                //tex[3][1] = -roadRepeatsBottom;
            }
            oldBottom = currentBottom;
            oldTop = currentTop;

            if(roadIndex < road.size() - 4)
            {
                leftPoint = point{road[roadIndex + 2], road[roadIndex + 3]};
                rightPoint = point{road[roadIndex + 4], road[roadIndex + 5]};
                middlePoint = getMiddle(leftPoint, rightPoint);

                point topLeftPointNext = rotate(middlePoint, leftPoint),
                    bottomLeftPointNext = rotate(middlePoint, leftPoint, OPPOSITE_PI_DIVIDED_BY_2),
                    topRightPointNext = rotate(middlePoint, rightPoint, OPPOSITE_PI_DIVIDED_BY_2),
                    bottomRightPointNext = rotate(middlePoint, rightPoint);

                double vectorXLeftTopLeft = topLeftPointNext.x - leftPoint.x, vectorYLeftTopLeft = topLeftPointNext.y - leftPoint.y, distanceLeftTopLeft = distance(leftPoint, topLeftPointNext), distanceSide = distance(leftPoint, rightPoint);
                vectorXLeftTopLeft /= distanceLeftTopLeft;
                vectorYLeftTopLeft /= distanceLeftTopLeft;

                topLeftPointNext.x = leftPoint.x + vectorXLeftTopLeft * roadSize;
                topLeftPointNext.y = leftPoint.y + vectorYLeftTopLeft * roadSize;

                bottomLeftPointNext.x = leftPoint.x - vectorXLeftTopLeft * roadSize;
                bottomLeftPointNext.y = leftPoint.y - vectorYLeftTopLeft * roadSize;

                double vectorXRightTopRight = topRightPointNext.x - rightPoint.x, vectorYRightTopRight = topRightPointNext.y - rightPoint.y, distanceRightTopRight = distance(rightPoint, topRightPointNext);
                vectorXRightTopRight /= distanceRightTopRight;
                vectorYRightTopRight /= distanceRightTopRight;
                topRightPointNext.x = rightPoint.x + vectorXRightTopRight * roadSize;
                topRightPointNext.y = rightPoint.y + vectorYRightTopRight * roadSize;
                bottomRightPointNext.x = rightPoint.x - vectorXRightTopRight * roadSize;
                bottomRightPointNext.y = rightPoint.y - vectorYRightTopRight * roadSize;

                bottomRightPoint = reverse(getIntersection(currentBottom, getLine(bottomLeftPointNext, bottomRightPointNext)));
                topRightPoint = reverse(getIntersection(currentTop, getLine(topLeftPointNext, topRightPointNext)));

                double roadRepeatsTop = Vector2D(getVector2D(topLeftPoint), getVector2D(topRightPoint)).length() / roadSize,
                   roadRepeatsBottom = Vector2D(getVector2D(bottomLeftPoint), getVector2D(bottomRightPoint)).length() / roadSize;

                // RIGHT

                /// TODO: texture adjustement ! EDIT: CODE DONE SEE UP TOO DOESN'T SEEMS TO PATCH TURNS TEXTURES

                //tex[1][1] = roadRepeatsTop;
                //tex[2][1] = roadRepeatsBottom;
            }

            double roadRepeats = distanceSide / roadSize;

            // used to have
            // tex[1][1] = roadRepeats;
            // tex[2][1] = roadRepeats;

            #define ELEVATING 2
            double vertex[4][3] = {{topLeftPoint.x, topLeftPoint.y, getGroundAltitude(topLeftPoint.x, topLeftPoint.y) + ELEVATING},
                                  {topRightPoint.x, topRightPoint.y, getGroundAltitude(topRightPoint.x, topRightPoint.y) + ELEVATING},
                                  {bottomRightPoint.x, bottomRightPoint.y, getGroundAltitude(bottomRightPoint.x, bottomRightPoint.y) + ELEVATING},
                                  {bottomLeftPoint.x, bottomLeftPoint.y, getGroundAltitude(bottomLeftPoint.x, bottomLeftPoint.y) + ELEVATING}};

            /// TODO: ROAD TEXTURE TRANSPARENCY !HIDE! ROAD BELOW !

            /*print(toString(topLeftPoint));
            print(toString(topRightPoint));
            print(toString(bottomLeftPoint));
            print(toString(bottomRightPoint));
            print();*//*

            //print(convertNbToStr(topLeftPoint.x) + " " + convertNbToStr(topLeftPoint.y) + " " + convertNbToStr(getGroundAltitude(topLeftPoint.x, topLeftPoint.y) + ELEVATING));
            roadsGlObjects[roadsType[roadsIndex]].addPart(tex, vertex);
        }
    }
    //print("loadRoads - end");
}

void initRoadsRender()
{
    // print("initRoadsRender - begin");
    for(unsigned int roadsIndex = 0; roadsIndex < ROADS_NUMBER; roadsIndex++)
    {
        roadsGlObjects[roadsIndex].initializeTexture();
        roadsEndGlObjects[roadsIndex].initializeTexture();
        roadsGlObjects[roadsIndex].initializeRender();
        roadsEndGlObjects[roadsIndex].initializeRender();
    }
    // print("initRoadsRender - end");
}

void renderRoads()
{
    for(unsigned int roadsIndex = 0; roadsIndex < ROADS_NUMBER; roadsIndex++)
    {
        roadsGlObjects[roadsIndex].render();
        roadsEndGlObjects[roadsIndex].render();
    }
}
*/
