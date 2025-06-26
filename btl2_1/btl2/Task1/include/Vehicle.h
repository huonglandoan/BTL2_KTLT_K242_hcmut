#ifndef VEHICLE_H
#define VEHICLE_H

#include "Unit.h"

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
string vehicleTypeToString(VehicleType type); 
class Vehicle : public Unit
{
    private:
    VehicleType vehicleType;

public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {}
    ~Vehicle(){}
    int getAttackScore();
    VehicleType getVehicleType() const {return vehicleType; }
    bool isVehicle() const {return true;}
    string str() const;
};

#endif // VEHICLE_H
