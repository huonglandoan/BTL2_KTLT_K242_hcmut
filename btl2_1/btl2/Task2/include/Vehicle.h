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
protected:
    VehicleType vehicleType;  // * Thể loại phương tiện

public:
    // * Constructor: khởi tạo với quantity, weight, pos, và vehicleType.
    int attackScore = -1;
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {}
    // * Override hàm getAttackScore: score = (vehicleType_value * 304) + (quantity * weight)
    int getAttackScore() override;
    VehicleType getVehicleType() const {return vehicleType; }
    // * Override hàm str: trả về chuỗi theo định dạng
    // * "Vehicle[vehicleType=<vehicleType>, quantity=<quantity>, weight=<weight>, pos=<pos>]"
    //bool isVehicle() const {return true;}
    string str() const override;
    // * Additional functions if possible
    void setWeight(int w) override{
        Unit::setWeight(w);
    }
    void setQuantity(int q) override{
        Unit::setQuantity(q);
    }
    Unit *clone() const override{
        return new Vehicle(getQuantity(), getWeight(), getCurrentPosition(), getVehicleType());
    }
};

#endif // VEHICLE_H
