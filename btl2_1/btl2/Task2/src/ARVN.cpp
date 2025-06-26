#include "ARVN.h"



void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
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
}
string ARVN::str() const {
    // TODO: Implement
    std::ostringstream oss;
    oss << "ARVN["
        << "LF=" << LF << ","
        << "EXP=" << EXP << ","
        << "unitList=" << (unitList ? unitList->str() : "null") 
        //<< "battleField=" << (battleField ? battleField->getName() : "null")
        << "]";

    return oss.str();
}

