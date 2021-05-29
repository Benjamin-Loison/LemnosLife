#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <map>

#include "../LemnosLife/Map/User/User.h"
#include "../LemnosLife/Map/User/View.h"
#include "../LemnosLife/Map/User/ViewGravity.h"
#include "../LemnosLife/Map/User/Inventory.h"
#include "../Network/Main/server.h"
// Gravity

class Seat // all seat code have been copied from client - some client side code have been removed and several code isn't used
{
    public:
        Seat();
        Seat(unsigned int vehicleId, Position position, bool isDriver = false, unsigned short seatId = 0);
        bool isEmpty(), isDriver();
        std::pair<bool, double> isPlayerInRange(User*);
        void setUser(User* = nullptr);
        User* getSeated();
        Position getPosition(), getRotatedPosition();
        unsigned int getVehicleId();
        unsigned short getSeatId();
    private:
        unsigned int m_vehicleId;
        User* m_seated;
        Position m_position;
        bool m_isDriver;
        unsigned short m_seatId;
};

enum VehicleType {AIRPLANE, HELICOPTER, BOAT, CAR, MOTO, VEHICLE_TYPE_NOT};

class Vehicle
{
    public:
        Vehicle();
        Vehicle(std::string, View/*Gravity*/, std::string, bool isLocked = true, bool isEngineRunning = false, bool isSirenRunning = false, Backpack* = nullptr);
        std::string toString(bool withId = true, bool toSend = false), sendToString(), containerToString(), getName(), getTexture();
        Backpack* getContainerPtr();
        //ViewGravity* getViewGravityPtr();
        View* getViewPtr();
        Seat* getSeat(User*);
        Position getPosition();
        double getSeatDistance(), getFuelConsumption(), getTankCapacity(), getFuel(), getFuelSpaceAvailable(), getPriceForFullFill();
        void addKey(std::string), removeKey(std::string), switchLock(), setView(Position, ViewAngle = ViewAngle()), setUserSeat(unsigned short seatId, User* user = nullptr, bool unseat = false),
             setEngineState(bool = false/*the default isn't used for the moment*/, bool sendToEveryone = false), removeFuelDistance(double),
             syncVehicleInventory(std::string exceptUsername = ""), changeSirenState(std::string withoutUsername = ""), removeKeys(), setSirenState(bool newSiren = false, std::string withoutUsername = "");
        bool isEmpty(), addFuel(double), getSirenState(), getEngineState();
        unsigned short getSeatsNumber(), getSeatNumber(User*);
        unsigned int getVehicleId();
        std::vector<Seat*> getOccupiedSeats();
        std::vector<std::string> getOtherPassengers(std::string exceptUsername = "");
    private:
        std::string m_name, m_texture;
        View/*Gravity*/ m_view/*Gravity*/; // can be interesting in the future to use the gravity feature on the server side
        View m_lastView;
        double m_lastAngle, m_seatDistance, m_tankCapacity, m_fuelConsumption, m_fuel;
        unsigned int m_id;
        Backpack* m_container;
        std::vector<Seat> m_seats;
        std::vector<std::string> m_keys;
        bool m_isLocked, m_isEngineRunning, m_siren, m_containerHaveSpace;
        VehicleType m_vehicleType;
};

unsigned int addVehicle(std::string, View/*Gravity*/, std::string = "", bool sendToUsers = true, bool isLocked = true, bool isEngineRunning = false, bool isSirenRunning = false, Backpack* container = nullptr)/*used to fill container pointer to the boolean sendToUsers so execute the else statement of Vehicle constructor*/;
void initializeVehicles(), saveVehicles(), removeVehicles(), deleteVehicle(unsigned int, bool doErase = true), addVehicleNetwork(User* user, std::string vehicleIdFormated, std::string textureIdFormated);
std::string allVehiclesToString(std::string startStr = "", bool withId = true, std::string delimiter = NETWORK_SEPARATOR_STR, bool toSend = false), allSeatsToString(User* user), allSirensToString(), allEnginesToString(), getVehicleNameWithoutConsideringCase(std::string), getVehicleTextureWithoutConsideringCase(std::string vehicleName, std::string textureName);

std::vector<std::string> getVehicleTextures(std::string vehicleName);
extern std::map<unsigned int, Vehicle> vehicles;
extern std::string vehiclesFolder;
Seat* getRidingVehicleSeat(User*);
bool doesVehicleExist(unsigned int);
Vehicle* getRidingVehicle(User*);
double nearestVehicleTo(View view);

#endif
