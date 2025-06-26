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

class Vehicle : public Unit
{
protected:
    VehicleType vehicleType;  // * Thể loại phương tiện
    int attackScore = -1;
    int modifiedScore = -1;
public:
    // * Constructor: khởi tạo với quantity, weight, pos, và vehicleType.
    
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {
        attackScore = (static_cast<int>(vehicleType) * 304 + quantity * weight) / 30.0;
        cout << "new Veh\n";
    }
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
    void setAttackScore(int score){
        modifiedScore = score;
    }
    void resetAttackScore(){
        modifiedScore = -1;
    }

};

#endif // VEHICLE_H
