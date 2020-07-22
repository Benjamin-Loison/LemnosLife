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
#include "../Input/input.h"
#include <map>
using namespace std;

vector<DynamicGl_object> vehicleModels;
map<string, unsigned int> vehicleIndexes;
map<unsigned int, Vehicle/*unsigned int*/> vehicles;
unsigned int availableId = 0;
string vehiclesSkins, vehiclesModels;
vector<tuple<unsigned int, string, string, ViewGravity>> vehiclesToAdd;

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
    double x = /*0*/-getRadians(viewAngle.getRoll())/*90*//*1.57*/, y = /*0*/getRadians(viewAngle.getTheta())/*90*//*1.57*/, z = -getRadians(viewAngle.getPhi()); // TODO: how to deal with theta ? - doing it ! :)
    return glm::vec3(x, y, z);
}

void initializeVehicles()
{
    //print("initializeVehicles() - begin");
    // g++ used to point here for bug 280520
    vehiclesSkins = picturesFolder + "Vehicles" + pathSeparatorStr;
    vehiclesModels = commonMapFolder + "Vehicles" + pathSeparatorStr;

    vector<string> vehicles = listFiles(vehiclesModels, "", true);
    //exitWithMessage(toString(folders));
    unsigned int vehiclesSize = vehicles.size();
    for(unsigned int vehiclesIndex = 0; vehiclesIndex < vehiclesSize; vehiclesIndex++)
    {
        string vehicle = vehicles[vehiclesIndex], vehicleName = getFileName(vehicle), vehicleFolder = vehiclesModels + vehicleName + pathSeparatorStr, vehicleConfig = vehicleFolder + vehicleName + ".txt", vehicleModel = vehicleFolder + vehicleName + ".struc";
        //print(vehicleName + "@" + vehicleModel + "@" + vehicleConfig);
        if(file_exists(vehicleModel) && file_exists(vehicleConfig))
        {
            vehicleIndexes[vehicleName] = vehicleModels.size();
            vehicleModels.push_back(loadFileStrucDynamic(vehicleModel));
            //print(vehicleName + " added !");
            //initializeVehicle(vehicleName);
            //DynamicGl_object(configurationData["urlTextureServer"] + line);
        }
    }
    //print("initializeVehicles() - end");
}

Force::Force() : m_norm(0), m_angle(0) {}

bool Force::isNull()
{
    return m_norm == 0;
}

Vehicle::Vehicle() {} // why required ?

Vehicle::Vehicle(unsigned int vehicleId, string vehicleName, string camouflage, ViewGravity viewGravity) : m_name(vehicleName), m_viewGravity(viewGravity), m_camouflage(camouflage), m_needInit(true), m_lastPosition(viewGravity.getGravityPosition()), m_firstRender(true), m_throttle(Force()), m_turn(0) // used to use the term camouflage - come back to it due to gluInt
{
    //addChatMessage(viewGravity.toString() + " " + m_viewGravity.toString());
    glm::vec3 coo = getVec3(&viewGravity), rot = getVec3ViewAngle(viewGravity.getViewAngle());
    unsigned int vehicleIndex = vehicleIndexes[vehicleName];
    //print(vehicleName + " " + toString(coo) + "@" + toString(rot) + "@" + convertNbToStr(vehicleIndex));
    unsigned int vehicleModelId = vehicleModels[vehicleIndex].add(coo, rot); /// need to be executed in a graphic thread (wasn't the case)
    //addChatMessage("id: " + convertNbToStr(vehicleModelId) + " " + convertNbToStr(vehicleIndex));
    //vehicleModels[vehicleIndex].modify(vehicleModelId, coo, rot);
    availableId++;
    m_id = availableId;
    m_idGPU = vehicleModelId;
    initializeVehicle();
}

Seat* Vehicle::getSeat(User* player)
{
    unsigned short seatsSize = m_seats.size();
    for(unsigned short seatsIndex = 0; seatsIndex < seatsSize; seatsIndex++)
    {
        Seat* seat = &m_seats[seatsIndex];
        if(seat->getSeated() == player)
            return seat;
    }
    return nullptr;
}

unsigned int Vehicle::getVehicleId()
{
    return m_id;
}

void addVehicles()
{
    //print("Vehicle::addVehicles() - begin");
    unsigned int vehiclesToAddSize = vehiclesToAdd.size();
    for(unsigned int vehiclesToAddIndex = 0; vehiclesToAddIndex < vehiclesToAdd.size(); vehiclesToAddIndex++)
    {
        tuple<unsigned int, string, string, ViewGravity> vehicleData = vehiclesToAdd[vehiclesToAddIndex];
        //addChatMessage("adding: " + (get<3>(vehicleData)).toString());
        //addChatMessage("add: " + convertNbToStr(get<0>(vehicleData)) + " " + get<1>(vehicleData) + " " + get<2>(vehicleData));
        vehicles[availableId] = Vehicle(get<0>(vehicleData), get<1>(vehicleData), get<2>(vehicleData), get<3>(vehicleData));
        //addChatMessage("vehicle added graphically !");
    }
    vehiclesToAdd.clear();
    //print("Vehicle::addVehicles() - end");
}

void addVehicle(unsigned int vehicleId, string vehicleName, string camouflageId, ViewGravity viewGravity) // vehicleNumericId, vehicleId, textureId, viewGravity
{
    vehiclesToAdd.push_back(make_tuple(vehicleId, vehicleName, camouflageId, viewGravity));
    //vehicles[availableId] = Vehicle(vehicleId, vehicleName, camouflageId, viewGravity);
}

void addVehicle(unsigned int vehicleId, string vehicleName, string camouflageId, View view) // vehicleNumericId, vehicleId, textureId, view
{
    ViewGravity viewGravity = ViewGravity(view);
    //viewGravity.updateViewAngle(ViewAngle(1.56, 1.56, 1.56/*45, 45, 45*/));
    //addChatMessage(view.toString() + " " + viewGravity.toString());
    vehiclesToAdd.push_back(make_tuple(vehicleId, vehicleName, camouflageId, viewGravity));
    //vehicles[availableId] = Vehicle(vehicleId, vehicleName, camouflageId, ViewGravity(view));
}

void Vehicle::addTurn(double toAdd)
{
    if(abs(toAdd) + abs(m_turn) < 1)
    {
        m_turn += toAdd;
    }
}

void Vehicle::initializeVehicle()
{
    //print("Vehicle::initializeVehicle() - begin");
    //initializeTexture();
    //initializeRender();
    string vehiclePath = vehiclesModels + m_name + pathSeparatorStr + m_name, vehicleFilePath = vehiclePath + STRUCTURE_FILE_EXTENSION; /// shouldn't be computed for every instance of a given vehicle
    vector<string> lines = getFileContent(vehiclePath + ".txt", false, false);
    //addChatMessage(vehiclePath);
    for(unsigned int i = 0; i < lines.size(); i++) /// should make a more precise model for collisions
    {
        string line = lines[i];
        vector<string> lineParts = split(line);
        unsigned short linePartsSize = lineParts.size();
        if(linePartsSize > 0)
        {
            if(lineParts[0] == "collisions")
            {
                if(linePartsSize > 4) // used to be 4 - and was nice (used to change with 5)
                {
                    for(unsigned short i = 1; i < 5; i++)
                    {
                        string coordinates = lineParts[i];
                        vector<string> coordinatesParts = split(coordinates, ";");
                        unsigned short coordinatesPartsSize = coordinatesParts.size();
                        if(coordinatesPartsSize > 2) // used to be 2 - and was also nice x) (used to change for 3 lol)
                        {
                            // TODO: check type
                            //print("hello my world !");
                            ///double x = convertStrToDouble(coordinatesParts[0]), y = convertStrToDouble(coordinatesParts[1]):µ, z = convertStrToDouble(coordinatesParts[2])*/; // could use z (cf 080320-1217)
                            ///m_collisions[i - 1] = point({x, y}); // used to use points
                            m_collisions[i - 1] = Vector3D(coordinates);
                            //print("init m_collisions: " + toString(m_collisions[i - 1]));
                        }
                    }
                }
            }
            else if(lineParts[0] == "driver" || lineParts[0] == "seat")
            {
                Position pos = Position(replace(line, lineParts[0] + " ", ""), ";");
                m_seats.push_back(Seat(m_id, pos, lineParts[0] == "driver"));
                //print("seat added !");
            }
        }
    }
    //print("Vehicle::initializeVehicle() - end");
}

void Vehicle::initializeTexture()
{
    //m_texture = addGetTexture(string(vehiclesSkins + m_name + m_camouflage + ".png"), "loadSkinTexture");
    //m_refreshSkinFinished = true;
}

void initializeVehicleTexture()
{
    //print("initializeVehicleTexture() - begin");
    unsigned int vehicleSize = vehicleModels.size();
    for(unsigned int vehicleIndex = 0; vehicleIndex < vehicleSize; vehicleIndex++)
    {
        vehicleModels[vehicleIndex].initializeTexture();
    }
    //print("initializeVehicleTexture() - end");
}

void initializeVehicleRender()
{
    //print("initializeVehicleRender() - begin");
    unsigned int vehicleSize = vehicleModels.size();
    for(unsigned int vehicleIndex = 0; vehicleIndex < vehicleSize; vehicleIndex++)
    {
        vehicleModels[vehicleIndex].initializeRender();
    }
    //print("initializeVehicleRender() - end");
}

void Vehicle::initializeRender() // considering all vehicles with different camouflage because of the future presence of many camouflage paints
{

}

void Vehicle::onVehicleMoved()
{
    //print("Vehicle::onVehicleMoved() - begin");
    unsigned short seatsSize = m_seats.size();
    for(unsigned short seatsIndex = 0; seatsIndex < seatsSize; seatsIndex++)
    {
        Seat* seat = &m_seats[seatsIndex];
        if(!seat->isEmpty())
        {
            User* seated = seat->getSeated();
            Position newPos = seat->getRotatedPosition() + getPosition(); // used not to have rotatiop
            seated->getViewGravity()->updatePosition(newPos);
            camera->checkChunk(); // should do it at a higher level
            bool isThePlayer = seated->getUsername() == configurationData["username"];
            if(isThePlayer)
            {
                newPos.addZ(eyeHeight);
                camera->setPosition(getVec3(newPos));
                //camera->VectorsFromAngles(false);
            }

            ///seated->updateViewGravity(ViewGravity(View(newPos/*, seated->getViewGravity()->getViewAngle()*/)), /*false*//*true*/isThePlayer, false);
            //addChatMessage(seated->getUsername() + " moved !");
        }
    }
    //print("Vehicle::onVehicleMoved() - 0");

    Position collisionsRotated[4];
    double heights[4], zMoyen = 0;
    //print("Vehicle::onVehicleMoved() - 00");
    ViewAngle viewAngle = m_viewGravity.getViewAngle(); /// BOTH FIRST AND BOTH LAST ARE FRONT OR BACK OF VEHICLE AND SAME ORDER (prefer left then right)
    //print("Vehicle::onVehicleMoved() - 01");
    //m_viewGravity.getViewAnglePtr()->setTheta(0);
    ///addChatMessage("vA: " + viewAngle.toString());
    for(unsigned short i = 0; i < 4; i++)
    {
        //print("Vehicle::onVehicleMoved() - 02 " + toString(m_collisions[i]) + " & " + viewAngle.toString());
        Position rotated = rotate(m_collisions[i], viewAngle); /// m_collisions[i];
        //print("Vehicle::onVehicleMoved() - 03");
        ///addChatMessage(convertNbToStr(i) + " rotated: " + rotated.toString());
        collisionsRotated[i] = getPosition() + rotated;
        //print("Vehicle::onVehicleMoved() - 04");
        heights[i] = getGroundAltitude(collisionsRotated[i]);
        //print("Vehicle::onVehicleMoved() - 05");
        zMoyen += heights[i]; // used to be 0 lol
        //print("Vehicle::onVehicleMoved() - 06");
        ///addChatMessage(convertNbToStr(i) + " " + toString(m_collisions[i]) + " " + collisionsRotated[i].toString() + " " + convertNbToStr(heights[i]));
    }
    //print("Vehicle::onVehicleMoved() - 07");
    zMoyen /= 4;
    //print("Vehicle::onVehicleMoved() - 1");
    // = getPosition() + m_collisions[0], backRight, frontLeft, frontRight; // names are fictive

    /// MODEL: FORCE TO BE ON THE GROUND ALWAYS
    /// FINAL MODEL: force frontLeft, frontRight and finally backRight (and don't care about backLeft) - bruh that could be ugly :/
    /// faire voler la roue qui est la plus petite en altitude au dessus du sol en fixant les trois autres "roues" (bords de soclde de collision) au sol

    // permutation circulaire doesn't help
    /// let fix two points from back and front from the same side (theta so) and minimize error on the selection of roll to keep "wheels" up to the ground (we don't do roll then theta because vehicles are most of the time longer than large
    //addChatMessage(convertNbToStr(heights[1]) + " " + convertNbToStr(heights[3]) + " " + convertNbToStr(heights[1] - heights[3])); // the distance in the line below strangely isn't constant...
    double deltaH = heights[1] - heights[3], deltaX = m_collisions[1].X/*collisionsRotated[1].getX()*/ - m_collisions[3].X/*collisionsRotated[3].getX()*/ /*distance(collisionsRotated[1], collisionsRotated[3])*/, ataned = atan(deltaH / deltaX)/* * epsilon(collisionsRotated[1].getY() - collisionsRotated[3].getY())*/ * epsilon(deltaX)/*doesn't seem to patch x- x+ y- y+ pb*/, theta = getDegrees(ataned); // right side arbitrary because Ben writes with his right hand :P (I wrote this line - Ben)
    //double z = getGroundAltitude(&m_viewGravity);
    double deltaYH0 = heights[0] - heights[2], deltaYH1 = heights[1] - heights[3], deltaY = m_collisions[0].Y - m_collisions[2].Y, deltaYH = deltaYH0;
    if(deltaYH0 < deltaYH1)
    {
        deltaYH = deltaYH1;
    }
    double roll = getDegrees(atan(deltaYH / deltaY))/* - 90*/; /// why bug with this patch ? - may be still shader
    //print("Vehicle::onVehicleMoved() - 2");

    m_viewGravity.getGravityPositionPtr()->setZ(/*z*/zMoyen); /// TODO: add and use getBarycenetr(vector<Position> in collisions.cpp sure ?
    // let take moyennes for angles: theta, roll
    //double zBackLeft = getGroundAltitude(), zBackRight, zFrontLeft, zFrontRight;
    ///addChatMessage(convertNbToStr(deltaH) + " " + convertNbToStr(deltaX) + " " + convertNbToStr(theta)/* + " " + convertNbToStr(ataned)*/);
    m_viewGravity.getViewAnglePtr()->setTheta(theta);
    //m_viewGravity.getViewAnglePtr()->setRoll(roll);
    //print("Vehicle::onVehicleMoved() - 3");

    glm::vec3 coo = getVec3(&m_viewGravity), rot = getVec3ViewAngle(m_viewGravity.getViewAngle());
    ///m_viewGravity.getViewAnglePtr()->setRoll(0);
    //addChatMessage("rot: " + toString(rot));
    //print("Vehicle::onVehicleMoved() - 4");
    vehicleModels[vehicleIndexes[m_name]].modify(m_idGPU, coo, rot); /// CE FOUTU BUG DE THETA ET ROLL QUI NE S'APPLIQUENT PAS VENAIT DU FAIT QUE LES SHADERS NE FAISAIENT PAS LEUR JOB POUR CES COMPOSANTES - Bravo Louis !
    /*rotation theta doesn't also work for items...
User doesn't have this problem - problem solved :) #Shader*/
    //print("Vehicle::onVehicleMoved() - end");
}

/// TODO: when enter to join, doesn't tp directly to seat ?!

unsigned int Seat::getVehicleId()
{
    return m_vehicleId;
}

bool Vehicle::isOnGround()
{
    return true; /// TODO:
}

void Vehicle::increaseThrottle(double toAdd)
{
    if(abs(m_throttle.getNorm()) + abs(toAdd) < 1) /// TODO: should do a function based system
    {
        m_throttle.increase(toAdd);
    }
}

void Force::increase(double toAdd)
{
    m_norm += toAdd;
    //addChatMessage("increased: " + convertNbToStr(toAdd));
}

void Vehicle::decreaseThrottle(double toRemove)
{
    m_throttle.decrease(toRemove);
}

void Vehicle::getOutUser(User* user)
{
    Seat* seat = getRidingVehicleSeat(user);
    if(seat != nullptr) // shouldn't go in the (non existing) else statement
    {
        addChatMessage("Vehicle::getOutUser out");
        seat->setUser(nullptr);
        user->setRidingVehicleId(UNSIGNED_INT_MAX);
        //onVehicleMoved();
    }
}

void Force::decrease(double toRemove)
{
    //if(m_norm >= toRemove)
    {
        m_norm -= toRemove;
    }
    /*else
    {
        m_norm = 0;
    }*/
}

void Force::setNorm(double newNorm)
{
    m_norm = newNorm;
}

void Vehicle::render() // computation function
{
    //print("Vehicle::render() - begin");
    if(m_firstRender)
    {
        //glm::vec3 coo = glm::vec3(0, 0, 10), rot = glm::vec3(0, 0, 0);
        //addChatMessage(m_viewGravity.toString());
        //addChatMessage("vehicle rendered !" + toString(coo) + " " + toString(rot));
        m_firstRender = false;
        onVehicleMoved();
    }
    else
    {
        //addChatMessage(convertNbToStr(isLeftKeyPressed) + " " + convertNbToStr(isRightKeyPressed) + " " + convertNbToStr(isForwardKeyPressed) + " " + convertNbToStr(isBackwardKeyPressed));
        if(isLeftKeyPressed || isRightKeyPressed)
        {
            if(!isRightKeyPressed || !isLeftKeyPressed) // otherwise both pressed cancel the turn
            {
                double turnToAdd = (isRightKeyPressed ? 1 : -1) * 0.01;
                addTurn(turnToAdd);
                //addChatMessage("turn added !");

                // need to rotating driver view otherwise fucking horrible to drive - doing so:
                ///thePlayer->getViewGravity()->getViewAnglePtr()->addPhi(turnToAdd); // should rename getViewGravity from User to getViewGravityPtr ?
                // if rotate thePlayer here doesn't rotate when slipping turning it doesn't turn player head
            }
        }
        if(isForwardKeyPressed || isBackwardKeyPressed)
        {
            if(!isForwardKeyPressed || !isBackwardKeyPressed)
            {
                increaseThrottle((isForwardKeyPressed ? 1 : -1) * 0.01);
                //addChatMessage("throttle added !");
            }
        }

        if(!m_throttle.isNull())
        {
            if(isOnGround())
            {
                /// vector 2D or angle for force ? - I believe the discussion here is useless because we only consider the norm for the moment
                // if no turn we keep angles as is
                // roll isn't important here
                Position pos = m_viewGravity.getGravityPosition();

                ViewAngle* viewAngle = m_viewGravity.getViewAnglePtr();

                ///addChatMessage("new throttle norm: " + convertNbToStr(m_throttle.getNorm()));
                ///addChatMessage("new turn: " + convertNbToStr(m_turn));

                double rPhi = viewAngle->getPhi(), rTheta = viewAngle->getTheta(); // object angles doesn't work here because not well initialized in comparaison with viewGravity which is rightly initialized

                pos.addX(m_throttle.getNorm() * cosDeg(rPhi)); /// maybe it is the reverse for phi angle ? - it seems correct
                pos.addY(m_throttle.getNorm() * sinDeg(rPhi));
                pos.addZ(m_throttle.getNorm() * sinDeg(rTheta));

                double turnToAdd = -m_turn * m_throttle.getNorm() * 10;
                viewAngle->addPhi(turnToAdd);
                /// here we turn player's head as the vehicle turn
                camera->addPhi(turnToAdd);

                m_viewGravity.updatePosition(pos);
                onVehicleMoved();

                /*const Uint8 *state = SDL_GetKeyboardState(NULL); // doesn't work #GrosBid

                if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])
                {
                    addTurn((state[SDL_SCANCODE_RIGHT] ? 1 : -1) * 0.01);
                }*/

                m_throttle.decrease(m_throttle.getNorm() / 100); /// should also be based a well thought function - should also be based on time duration and not frame counter
                m_turn *= 0.99;

                if(abs(m_turn) < 0.001)
                {
                    m_turn = 0;
                }
                if(abs(m_throttle.getNorm()) < 0.001)
                {
                    m_throttle.setNorm();
                }
            }
        }
    }
    //print("Vehicle::render() - end");
}

double Vehicle::getSpeed()
{
    return m_throttle.getNorm();
}

string Vehicle::getName()
{
    return m_name;
}

double Force::getNorm()
{
    return m_norm;
}

double Force::getAngle()
{
    return m_angle;
}

pair<unsigned short, double> Vehicle::isPlayerInRange(User* user)
{
    unsigned short seatsSize = m_seats.size();
    //addChatMessage("seats nb: " + convertNbToStr(seatsSize));
    for(unsigned short seatsIndex = 0; seatsIndex < seatsSize; seatsIndex++)
    {
        //addChatMessage("seatiii");
        pair<bool, double> inRangeDistance = m_seats[seatsIndex].isPlayerInRange(user);
        if(inRangeDistance.first)
        {
            //addChatMessage("seatooo");
            return make_pair(seatsIndex, inRangeDistance.second);
        }
    }
    //addChatMessage("da");
    return make_pair(UNSIGNED_SHORT_MAX, 0);
}

bool Vehicle::isSeatEmpty(unsigned short seatId)
{
    return seatId >= m_seats.size() ? false : m_seats[seatId].isEmpty();
    /*if(seatId >= m_seats.size())
        return false; // this shouldn't happened
    return m_seats[seatId].isEmpty();*/
}

void Vehicle::setUserSeat(unsigned short seatId, User* user)
{
    //addChatMessage("Vehicle::setUserSeat");
    if(seatId < m_seats.size())
    {
        addChatMessage("Vehicle::setUserSeat in");
        m_seats[seatId].setUser(user);
        user->setRidingVehicleId(m_id);
        onVehicleMoved();
    }
    // else shouldn't happened
}

Position Vehicle::getPosition()
{
    return m_viewGravity.getGravityPosition();
}

void renderVehicles()
{
    //print("renderVehicles() - begin");
    for(map<unsigned int, Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++) // this loop is just a computation one
    {
        it->second.render();
    }
    unsigned int vehicleSize = vehicleModels.size();
    for(unsigned int vehicleIndex = 0; vehicleIndex < vehicleSize; vehicleIndex++)
    {
        vehicleModels[vehicleIndex].render();
    }
    //print("renderVehicles() - end");
}

Seat::Seat() {}

Seat::Seat(unsigned int vehicleId, Position position, bool isDriver) : m_vehicleId(vehicleId), m_position(position), m_isDriver(isDriver), m_seated(nullptr) // add a seat id ?
{

}

bool Seat::isEmpty()
{
    return m_seated == nullptr;
}

bool Seat::isDriver()
{
    return m_isDriver;
}

User* Seat::getSeated()
{
    return m_seated;
}

Position Seat::getPosition()
{
    return m_position;
}

ViewGravity* Vehicle::getViewGravityPtr()
{
    return &m_viewGravity;
}

Position Seat::getRotatedPosition()
{
    Vehicle* vehicle = &vehicles[m_vehicleId];

    ViewAngle viewAngle = vehicle->getViewGravityPtr()->getViewAngle();
    //addChatMessage("viewAngle: " + viewAngle.toString());
    Vector3D seatPositonVec = rotate(m_position, viewAngle);
    return Position(seatPositonVec);
}

pair<bool, double> Seat::isPlayerInRange(User* user)
{
    Vehicle* vehicle = &vehicles[m_vehicleId];

    Position vehiclePosition = vehicle->getPosition(), playerPosition = user->getViewGravity()->getGravityPosition();
    double distanceUserSeat = distance(playerPosition, getRotatedPosition()/*used not to have rotation*/ + vehiclePosition); /// TODO: need rotation WITH ALL THREE "AXIS"
    //addChatMessage("d: " + convertNbToStr(distanceUserSeat) + " " + user->getViewGravity()->getGravityPosition().toString() + " " + m_position.toString());
    return make_pair(distanceUserSeat <= DISTANCE_USER_VEHICLE_DOOR, distanceUserSeat); // 1 meter
}

void Seat::setUser(User* user)
{
    //addChatMessage("s0: " + convertNbToStr(m_seated != nullptr));
    m_seated = user;
    //addChatMessage("s1: " + convertNbToStr(m_seated != nullptr));
    //addChatMessage("user now seated !");
}

Seat* getRidingVehicleSeat(User* player)
{
    unsigned int ridingVehicleId = player->getRidingVehicleId();
    if(ridingVehicleId == UNSIGNED_INT_MAX)
        return nullptr;
    return vehicles[ridingVehicleId].getSeat(player);
}

Vehicle* getRidingVehicle(User* player)
{
    Seat* seat = getRidingVehicleSeat(thePlayer);
    if(seat == nullptr)
        return nullptr;
    unsigned int ridingVehicleId = seat->getVehicleId();
    if(ridingVehicleId == UNSIGNED_INT_MAX)
        return nullptr;
    return &vehicles[ridingVehicleId];
}

/*

Vehicle::render

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
        gP.setZ(0.05    /*get<DOUBLE>(mapData)["seaHeight"]*//*);
        viewGravity->updatePosition(gP);
        Position newPos = viewGravity->getGravityPosition();
        if(newPos != m_lastPosition || angle != m_lastAngle)
        {
            for(unsigned short i = 0; i < 4; i++)
            {
                point ptRot = getPoint(newPos);
                point pt = sumPoint(ptRot, rotate(m_collisions[i], point({0, 0}), angle));
                double altitude = getGroundAltitude/*WithStructure*//*(pt.x, pt.y/*, 10*//*); // TODO: should consider structures !
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
        /*glm::vec3 vec = getVec3(newPos);
        modelview = glm::translate(modelview, vec/*glm::vec3(x, y, z));*//*
        modelview = glm::rotate(modelview, (float)glm::radians(/*m_viewGravity.getViewAngle().getPhi()*//*angle/* + 90*//*), glm::vec3(0, 0, 1));
        glm::mat4 modelviewProjection = getProjection() * modelview;
        shader.setMat4("modelviewProjection", modelviewProjection);
        glDrawArrays(GL_TRIANGLES, 0, verticesNumber); ///

        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Vehicle::initializeRender

        //print("Vehicle file: " + vehicleFilePath);
    /*lines = getFileContent(vehicleFilePath);

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
        }*//*
        vector<double> texTmp;
        for(unsigned short x = 0; x < 4; x++) /// TODO: do like Structures ? but how to manage rotation ? so here need king of adapter to make quadrilateral two triangles and don't manage camouflage for the moment
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
        for(unsigned short x = 0; x < 4; x++) /// TODO: do like Structures ? but how to manage rotation ? so here need king of adapter to make quadrilateral two triangles and don't manage camouflage for the moment
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

*/
