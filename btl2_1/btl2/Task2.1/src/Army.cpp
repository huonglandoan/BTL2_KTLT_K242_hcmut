#include "Army.h"

Army::Army(Unit **unitArray, int size, string name) : name(name) {
    // TODO: Implement
    unitList = new UnitList(size);
    LF = 0;
    EXP = 0;
    for (int i = 0; i < size; ++i) {
    Unit* unit = unitArray[i];

        if (Vehicle* v = dynamic_cast<Vehicle*>(unit)) {
            unitList->insert(v);
            LF += safeCeil(v->getAttackScore());
           // cout << "Vehicle detected" << endl;
        }
        else if (Infantry* inf = dynamic_cast<Infantry*>(unit)) {
            unitList->insert(inf);
            EXP += safeCeil(inf->getAttackScore());
           // cout << "Infantry detected" << endl;
        }
    }

    checkRange(LF, 1000);
    checkRange(EXP, 500);

}

Army::~Army() {
    // TODO: Implement
    if (unitList != nullptr) {
        delete unitList;
        unitList = nullptr;
    }
}

void Army::fight(Army* enemy, bool defense) {
    // TODO: Implement
}

void Army::updateScore(bool update){
    // TODO: Implement
   if(update){
    LF = 0;
    EXP = 0;
   
    for(Unit *unit : unitList->getUnits()){
    if (Vehicle* v = dynamic_cast<Vehicle*>(unit)) {
        LF += safeCeil(v->getAttackScore());
    }
    else if (Infantry* inf = dynamic_cast<Infantry*>(unit)) {
        EXP += safeCeil(inf->getAttackScore());
    }
}
    checkRange(LF, 1000);
    checkRange(EXP, 500);
}
}

string Army::str() const {
    return "Army[name=" + name + ",LF=" + to_string(LF) + ",EXP=" + to_string(EXP) + "]";
}


Unit* Army::cloneUnit(Unit* unit) {
    if (unit) {
        return unit->clone();
    }
    return nullptr;
}