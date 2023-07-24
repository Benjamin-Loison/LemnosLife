#ifndef DEF_VEHICLE
#define DEF_VEHICLE

#include "../LemnosLife/Map/User/ViewGravity.h"
#include "../LemnosLife/Map/User/View.h"
#include "../LemnosLife/Render/Shader.h"
#include "../2D/vector2d.h"
#include "../LemnosLife/Map/DynamicGl_object.h"
#include "../LemnosLife/Map/User/User.h"
#include "../LemnosLife/Map/User/Inventory.h"
#include <string>
#include <atomic>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define TURN_OFF_THE_ENGINE "Turn off the engine"
#define TURN_ON_THE_ENGINE "Turn on the engine"

#include <glm/glm.hpp>

//#define DISTANCE_USER_VEHICLE_DOOR 1
// isn't used anymore, replaced with seatDistance

class Seat
{
public:
    Seat();
    Seat(unsigned int vehicleId, Position position, bool isDriver = false, unsigned short seatId = 0); //
    bool isEmpty(), isDriver();
    std::pair<bool, double> isPlayerInRange(User*);
    void setUser(User*);
    User* getSeated();
    Position getPosition(), getRotatedPosition();
    unsigned int getVehicleId();
    unsigned short getSeatId();
private:
    // TODO: guns...
    unsigned int m_vehicleId;
    unsigned short m_seatId;
    User* m_seated;
    Position m_position;
    bool m_isDriver;
};

class Force
{
public:
    Force();
    bool isNull();
    void increase(double), decrease(double), setNorm(double = 0);
    double getNorm(), getAngle();
private:
    double m_norm, m_angle;
};

enum VehicleType {AIRPLANE, HELICOPTER, BOAT, CAR, MOTO, VEHICLE_TYPE_NOT}; // let's implement last possibility to avoid world wide Car default

class Vehicle
{
public:
    Vehicle();
    Vehicle(unsigned int, std::string, std::string, ViewGravity, bool isLocked, Backpack* container/* = nullptr*//*otherwise doesn't initialize and could involve crash because of NPE*/);
    void initializeRender(), render(), initializeVehicle(), initializeTexture(), initializeVehicles(), setUserSeat(unsigned short, User* = nullptr), increaseThrottle(double), decreaseThrottle(double), getOutUser(User*), addTurn(double), changeSirenBool(),
         /*, turnOnEngine(), turnOffEngine()*/removeFuelDistance(double distance), gasStationFillVehicle(), repair(), setView(Position, ViewAngle = ViewAngle()), updateGraphics(), computeOBB(Position = Position()), setSpeed(double = 0), setContainer(std::string containerStr),
         movePassengers(), initializeGraphic(), onVehicleMoved(/*bool justMovePassengers = false*/bool preciseVehicleId = false, bool needSend = true), setSirenBool(bool siren); // onVehicleMoved used to be private before repairman job
    std::pair<unsigned short, double> isPlayerInRange(User*);
    bool isSeatEmpty(unsigned short), isOnGround(), isEngineRunning(), setEngineState(bool = false), addFuel(double fuelQuantity), isEmpty(), haveAWheelInWater(), isLocked(), switchLock(), hasSpaceContainer();
    Position getPosition(), getContainerPosition(), getContainerPositionRotated();
    Seat* getSeat(User*);
    unsigned int getVehicleId(), getGPUId();
    double getSpeed(), getSeatDistance(), getF5Distance(), getKmh(), getFuelConsumption(), getTankCapacity(), getFuel(), getFuelSpaceAvailable(), getPriceForFullFill();
    Backpack* getContainerPtr();
    std::string getName(), getTranslatedName(), getCamouflage(), getTranslatedSpeed();
    ViewGravity* getViewGravityPtr();
    OBB* getOBBPtr();
    ViewGravity m_viewGravity; // used to be private before moveVehicleToPosition for repairman job
    VehicleType getVehicleType();
private:
    std::string m_name, m_camouflage, m_engineSound;
    bool m_isABoat, m_needInit, m_refreshSkinFinished, m_firstRender/*, m_firstSiren*/, m_isLocked, m_hasSpaceContainer;
    std::atomic<bool> m_siren, m_isEngineRunning; /// TODO: could be cool to make playSound etc work with classical boolean and not atomic one when not required
    //unsigned int m_VBO, m_VAO, texNumber, verticesNumber;
    //GLuint m_texture;
    //Shader shader;
    ///point m_collisions[4];
    Vector3D m_collisions[4];
    Position m_lastPosition, m_containerPosition; // may have multiple containers ?
    std::vector<Seat> m_seats;
    std::vector<std::string> m_keys;
    double m_phi, m_theta, m_roll, m_turn, m_seatDistance, m_top, m_F5Distance, m_tankCapacity, m_fuelConsumption, m_fuel, m_engineHeight, m_speed, m_maxSpeed, m_lastVehicleAngle;//, m_lastAngle; - I believe roll is the reason why we don't use ViewGravity (maybe we should add roll parameter to ViewAngle ?)
    // fuel: https://fr.wikipedia.org/wiki/Volkswagen_Polo_VI#Essence
    unsigned int m_id, m_idGPU;
    void removeFuel(double);
    VehicleType m_vehicleType;
    Force m_throttle;
    Backpack* m_container; // should rename backpack to container ? - should also make a destructor to remove this from memory at the end of use of vehicle
    OBB m_box;
};

//#define MAXIMAL_VEHICLE_DISTANCE 4
#define MAXIMAL_VEHICLE_DISTANCE 10

extern std::vector<DynamicGl_object> vehicleModels;
void addVehicle(unsigned int vehicleId, std::string vehicleName, std::string camouflageId, bool isLocked, ViewGravity viewGravity),
     addVehicle(unsigned int vehicleId, std::string vehicleName, std::string camouflageId, View view, bool isLocked, std::string containerStr),
     renderVehicles(),
     initializeVehicles(),
     initializeVehicleTexture(),
     initializeVehicleRender(),
     addVehicles(),
     turnOffEngine(unsigned int),
     turnOnEngine(unsigned int),
     gasStationFillVehicle(unsigned int),
     takeToPound(unsigned int),
     inspectOwners(unsigned int),
     moveVehicleToPosition(unsigned int),
     deleteVehicle(unsigned int),
     updateVehicleGraphics(bool needSend = true),
     removeVehicles();
glm::vec3 getVec3(Vector3D);
extern std::map<unsigned int, Vehicle*> vehicles; /// using pointers in vector or map of objects is better because we can use in these objects atomic variables (which solved for instance for vehicles, the thread problem?) cf (https://stackoverflow.com/questions/34382440/shared-variables-in-c11)
extern std::map<std::string, unsigned int> vehicleIndexes;
Seat* getRidingVehicleSeat(User*);
Vehicle* getRidingVehicle(User*), *getTargetingVehicle(double maxDistance = MAXIMAL_VEHICLE_DISTANCE);
double distance(User*, Vehicle*), distancePlayerToPlayer(User*, User*);
extern bool vehicleCollisionsDebug, vehiclesInitialized, readyToAddVehicles;
extern std::atomic<bool> vehiclesToAddEmpty;
std::string toString(VehicleType), vehiclesToString();

// cosSinTables

extern float* cosTable, *sinTable;
extern unsigned int cosSinTableSize;
extern double cosSinTableUpperBound;


// not using VEHICLES_SAVE here because problem with include in DynamicGl_Object header otherwise

#endif
