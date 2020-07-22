#ifndef DEF_VEHICLE
#define DEF_VEHICLE

#include "../LemnosLife/Map/User/ViewGravity.h"
#include "../LemnosLife/Map/User/View.h"
#include "../LemnosLife/Render/Shader.h"
#include "../2D/vector2d.h"
#include "../LemnosLife/Map/DynamicGl_object.h"
#include "../LemnosLife/Map/User/User.h"
#include <string>
#include "gl.h"

#define DISTANCE_USER_VEHICLE_DOOR 1

class Seat
{
    public:
        Seat();
        Seat(unsigned int vehicleId, Position position, bool isDriver = false);
        bool isEmpty(), isDriver();
        std::pair<bool, double> isPlayerInRange(User*);
        void setUser(User*);
        User* getSeated();
        Position getPosition(), getRotatedPosition();
        unsigned int getVehicleId();
    private:
        // TODO: guns...
        unsigned int m_vehicleId;
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

class Vehicle
{
    public:
        Vehicle();
        Vehicle(unsigned int, std::string, std::string, ViewGravity);
        void initializeRender(), render(), initializeVehicle(), initializeTexture(), initializeVehicles(), setUserSeat(unsigned short, User*), increaseThrottle(double), decreaseThrottle(double), getOutUser(User*), addTurn(double);
        std::pair<unsigned short, double> isPlayerInRange(User*);
        bool isSeatEmpty(unsigned short), isOnGround();
        Position getPosition();
        Seat* getSeat(User*);
        unsigned int getVehicleId();
        double getSpeed();
        std::string getName();
        ViewGravity* getViewGravityPtr();
    private:
        std::string m_name, m_camouflage;
        bool m_siren, m_isABoat, m_needInit, m_refreshSkinFinished, m_firstRender;
        //unsigned int m_VBO, m_VAO, texNumber, verticesNumber;
        ViewGravity m_viewGravity;
        //GLuint m_texture;
        //Shader shader;
        ///point m_collisions[4];
        Vector3D m_collisions[4];
        Position m_lastPosition;
        std::vector<Seat> m_seats;
        double m_phi, m_theta, m_roll, m_turn;//, m_lastAngle; - I believe roll is the reason why we don't use ViewGravity (maybe we should add roll parameter to ViewAngle ?)
        unsigned int m_id, m_idGPU;
        void onVehicleMoved();
        Force m_throttle;
};

extern std::vector<DynamicGl_object> vehicleModels;
void addVehicle(unsigned int vehicleId, std::string vehicleName, std::string camouflageId, ViewGravity viewGravity), addVehicle(unsigned int vehicleId, std::string vehicleName, std::string camouflageId, View view), renderVehicles(), initializeVehicles(), initializeVehicleTexture(), initializeVehicleRender(), addVehicles();
glm::vec3 getVec3(Vector3D);
extern std::map<unsigned int, Vehicle> vehicles;
Seat* getRidingVehicleSeat(User*);
Vehicle* getRidingVehicle(User*);

#endif
