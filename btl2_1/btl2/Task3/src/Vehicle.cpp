#include "Vehicle.h"

// TODO: implement
string vehicleTypeToString(VehicleType type) {
    switch(type){
        case TRUCK: return "TRUCK";
        case MORTAR: return "MORTAR";
        case ANTIAIRCRAFT: return "ANTIAIRCRAFT";
        case ARMOREDCAR: return "ARMOREDCAR";
        case APC: return "APC";
        case ARTILLERY: return "ARTILLERY";
        case TANK: return "TANK";
        default: return "UNKNOWN";
    }
}
string Vehicle::str() const
{
    ostringstream oss;
    oss << "Vehicle[vehicleType=" << vehicleTypeToString(getVehicleType())
        << ",quantity=" << quantity
        << ",weight=" << weight
        << ",position=" << pos.str()
        << "]";

    return oss.str();
}
int Vehicle::getAttackScore() {
    //return 
    if (modifiedScore != -1) {
        return modifiedScore;
    }
    return safeCeil((vehicleType * 304 + quantity * weight) / 30.0);
} 