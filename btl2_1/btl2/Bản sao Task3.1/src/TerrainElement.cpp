#include "TerrainElement.h"
#include "LiberationArmy.h"

//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------

// Constructor và Destructor của TerrainElement
TerrainElement::TerrainElement(Position pos, TerrainType terrainType) : pos(pos), terrain(terrainType){}

TerrainElement::~TerrainElement() {
    // Giải phóng tài nguyên nếu có
}

// Road: không có hiệu ứng
void Road::getEffect(Army *army) {
    cout << "road\n";
    if(army == nullptr){
        return;
    }
}

void Mountain::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    cout << "mountain\n";
    int deltaEXP = 0;
    int deltaLF = 0;
        if(army->isLiberationArmy()){
            //cout << "liber Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);
                //cout << dis << endl;
                if (dis <= 2.0) {
                    if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                        deltaEXP += safeCeil(inf->getAttackScore() * 1.3) - inf->getAttackScore(); 
                        inf->setAttackScore(safeCeil(inf->getAttackScore() * 1.3));
                    }else if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                        //cout << safeCeil(veh->getAttackScore() * 0.1) << endl;
                        deltaLF -= veh->getAttackScore() - safeCeil(veh->getAttackScore() * 0.9);
                        veh->setAttackScore(safeCeil(veh->getAttackScore() * 0.9));
                    }
                }
            }
        }else if(army->isARVNArmy()){
            //cout << "Arvn Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);

            if (dis <= 4) {
                if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                    deltaEXP += safeCeil(inf->getAttackScore() * 1.2) - inf->getAttackScore();
                    inf->setAttackScore(safeCeil(inf->getAttackScore() * 1.2));
                }
                if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                    deltaLF -= veh->getAttackScore() - safeCeil(veh->getAttackScore() * 0.95);
                    veh->setAttackScore(safeCeil(veh->getAttackScore() * 0.95));
                }
            }
        }
    }
    int newEXP = army->getEXP() + deltaEXP;
    int newLF = army->getLF()  + deltaLF;
    
    army->checkRange(newEXP, 500);
    army->checkRange(newLF, 1000);
    army->setEXP(newEXP);
    army->setLF(newLF);
}
// River: stub – giảm EXP của lực lượng bộ binh 10% nếu nằm trong bán kính 2 đơn vị
void River::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    cout << "river\n";

        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
        
        if(dis <= 2){
            if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                inf->setAttackScore(safeCeil(inf->getAttackScore() * 0.9));                 
            }
        }
    }
}

// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    cout << "urban\n";

    // int deltaEXP = 0;
    // int deltaLF = 0;
    if(army->isLiberationArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
            if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                if (inf->getInfantryType() == InfantryType::SPECIALFORCES || inf->getInfantryType() == InfantryType::REGULARINFANTRY) {
                    if(dis <= 5){
                        // deltaEXP += safeCeil((2*inf->getAttackScore())/ dis);
                        inf->setAttackScore(inf->getAttackScore() + safeCeil((2*inf->getAttackScore())/ dis));
                    }
                }
            }else if (Vehicle *veh = dynamic_cast<Vehicle*>(u)){
                if(dis <= 2){
                    if (veh->getVehicleType() == VehicleType::ARTILLERY) {
                        // deltaLF -= veh->getAttackScore() - safeCeil(veh->getAttackScore() * 0.5);
                        veh->setAttackScore(veh->getAttackScore() * 0.5);
                    }    
                }
            }
        }
    }else if(army->isARVNArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
    
            if(dis <= 3){
                if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                    if (inf->getInfantryType() == InfantryType::REGULARINFANTRY) {
                        // deltaEXP += safeCeil((3*inf->getAttackScore()) / (2 * dis));  
                        inf->setAttackScore(inf->getAttackScore() + safeCeil((3*inf->getAttackScore()) / (2 * dis)));
                    }
                }
            }
        }
    }
    // int newEXP = army->getEXP() + deltaEXP;
    // int newLF = army->getLF()  + deltaLF;
    
    // army->checkRange(newEXP, 500);
    // army->checkRange(newLF, 1000);
    // army->setEXP(newEXP);
    // army->setLF(newLF);
}
// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    cout << "fortification\n";

    // int deltaEXP = 0;
    // int deltaLF = 0;
    if(army->isLiberationArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
            
        if(dis <= 2){
            if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                // deltaEXP -= inf->getAttackScore() - safeCeil(inf->getAttackScore() * 0.8);     
                inf->setAttackScore(safeCeil(inf->getAttackScore() * 0.8));
            }else if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                // deltaLF -= veh->getAttackScore() - safeCeil(veh->getAttackScore() * 0.8);
                veh->setAttackScore(safeCeil(veh->getAttackScore() * 0.8));  
                }
            }
        }
    }else if(army->isARVNArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);

            if(dis <= 2){
                if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                    // deltaEXP += safeCeil(inf->getAttackScore() * 1.2)  - inf->getAttackScore();     
                    inf->setAttackScore(safeCeil(inf->getAttackScore() * 1.2));
                }else if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                    // deltaLF += safeCeil(veh->getAttackScore() * 1.2) - veh->getAttackScore();
                    veh->setAttackScore(safeCeil(veh->getAttackScore() * 1.2));  
                    }
            }
        }
    }
    // int newEXP = army->getEXP() + deltaEXP;
    // int newLF = army->getLF()  + deltaLF;
    
    // army->checkRange(newEXP, 500);
    // army->checkRange(newLF, 1000);
    // army->setEXP(newEXP);
    // army->setLF(newLF);
}
// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    cout << "specialzone\n";

    // int deltaEXP = 0;
    // int deltaLF = 0;
    for (Unit *u : army->getUnitList()->getUnits()) {
        double dis = calculateDistance(u->getCurrentPosition(), this->pos);

        if (dis <= 1) {
            if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                // deltaEXP -= inf->getAttackScore();
                inf->setAttackScore(0);
            } else if (Vehicle *vehicle = dynamic_cast<Vehicle*>(u)) {
                // deltaEXP -= vehicle->getAttackScore();
                vehicle->setAttackScore(0);
            }
        }
    }
    // int newEXP = army->getEXP() + deltaEXP;
    // int newLF = army->getLF()  + deltaLF;
    
    // army->checkRange(newEXP, 500);
    // army->checkRange(newLF, 1000);
    // army->setEXP(newEXP);
    // army->setLF(newLF);
}