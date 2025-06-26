#include "ARVN.h"

// TODO: Implement
ARVN::ARVN(Unit** unitArray, int size, string name, BattleField *battleField) 
        : Army(unitArray, size, name, battleField), unitArray(unitArray) {
    this->unitArray = new Unit*[size];
    size_V = 0;
    size_I = 0;

    for (int i = 0; i < size; ++i) {
        this->unitArray[i] = cloneUnit(unitArray[i]);  // Chỉ clone thôi
        if (dynamic_cast<Vehicle*>(unitArray[i])) size_V++;
        else if (dynamic_cast<Infantry*>(unitArray[i])) size_I++;
    }
}

void ARVN::fight(Army* enemy, bool defense) {
    if(!defense){
        for(Unit *u : this->getUnitList()->getUnits()){
            int newQuantity = safeCeil((u->getQuantity() * 0.8)); // Làm tròn đúng
            u->setQuantity(newQuantity);
            
            if(u->getQuantity() == 1){
                this->getUnitList()->remove(u);
            }
        }
    } else  {
        if(this->isDefeated()){   
                for(Unit *u : this->getUnitList()->getUnits()){
                this->getUnitList()->remove(u);
                }
        }else{
            for(Unit *u : this->getUnitList()->getUnits()){
                u->setWeight(safeCeil(u->getWeight()*0.8));
        }
    }
}
updateScore(true);
enemy->updateScore(true);
}

string ARVN::str() const {
        // TODO: Implement
        std::ostringstream oss;
        oss << "ARVN["
            << "LF=" << LF << ","
            << "EXP=" << EXP << ","
            << "unitList=" << (unitList ? unitList->str() : "null") 
            << ",battleField=" << (battleField != 0 ? battleField->str() : "")
            << "]";
        return oss.str();
    }
    
