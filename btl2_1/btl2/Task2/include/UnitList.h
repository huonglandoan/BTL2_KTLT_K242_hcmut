#ifndef _H_UNITLIST_H_
#define _H_UNITLIST_H_

#include "Infantry.h"
#include "Vehicle.h"

class UnitList
{
private:
struct Node{
    Unit *unit;
    Node *next;
    Node(Unit *unit): unit(unit), next(nullptr) {}
};
    Node *head, *tail;
    int count; 
    int capacity;

public:
    UnitList(int capacity);
    ~UnitList();
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    bool isSpecial(int n)   const;
    int countV() const ;
    int countI() const ;
    vector<Unit *> getUnits() const;
    string str() const;
    void remove(Unit *unit);
    vector<Unit*>getInfantryUnits() const;
    vector<Unit*>getVehicleUnits() const;
    //void Insert(Unit* unit);
    Unit* findVehicle(VehicleType type);
    Unit* findInfantry(InfantryType type);
    void clear();
    void addUnit(Unit *u);
    void CheckAndRemove();
    void insertToTail(Unit* unit);
    // * Additional functions if possible
};

#endif
