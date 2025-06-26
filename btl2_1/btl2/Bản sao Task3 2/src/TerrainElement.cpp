#include "TerrainElement.h"
#include "LiberationArmy.h"

double calculateDistance(const Position& pos1, const Position& pos2) {
    int rowDiff = pos1.getRow() - pos2.getRow();
    int colDiff = pos1.getCol() - pos2.getCol();
    return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
}
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
    if(army == nullptr){
        return;
    }
}

void Mountain::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    int deltaEXP = 0;
    int deltaLF = 0;
        if(army->isLiberationArmy()){
            cout << "liber Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);

                if (dis <= 2) {
                    if (dynamic_cast<Infantry*>(u)) {
                        Infantry *inf = dynamic_cast<Infantry*>(u);
                        deltaEXP += safeCeil(inf->getAttackScore() * 0.3);
                    }
                    if (dynamic_cast<Vehicle*>(u)) {
                        Vehicle *veh = dynamic_cast<Vehicle*>(u);
                        deltaLF -= safeCeil(veh->getAttackScore() * 0.1);
                    }
                }
            }
        }else if(army->isARVNArmy()){
            //cout << "Arvn Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);

            if (dis <= 4) {
                if (dynamic_cast<Infantry*>(u)) {
                    Infantry *inf = dynamic_cast<Infantry*>(u);
                    deltaEXP += safeCeil(inf->getAttackScore() * 0.2);
                }
                if (dynamic_cast<Vehicle*>(u)) {
                    Vehicle *veh = dynamic_cast<Vehicle*>(u);
                    deltaLF -= safeCeil(veh->getAttackScore() * 0.05);
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
    int deltaEXP = 0;
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
        
        if(dis <= 2){
            if (dynamic_cast<Infantry*>(u)) {
                Infantry *inf = dynamic_cast<Infantry*>(u);
                deltaEXP -= safeCeil(inf->getAttackScore() * 0.1);                 
            }
        }
    }
    int newEXP = army->getEXP() + deltaEXP;
    army->checkRange(newEXP, 500);
    army->setEXP(newEXP);
}

// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    int deltaEXP = 0;
    int deltaLF = 0;
    if(army->isLiberationArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
    
            if(dis <= 5){
                if (dynamic_cast<Infantry*>(u)) {
                    Infantry *inf = dynamic_cast<Infantry*>(u);
                    if (inf->getInfantryType() == InfantryType::SPECIALFORCES || inf->getInfantryType() == InfantryType::REGULARINFANTRY) {
                        double curAttackScore = inf->getAttackScore();
                        deltaEXP += safeCeil(curAttackScore + (2 * curAttackScore / dis));                 
                    }
                }else if (dis <= 2 && dynamic_cast<Vehicle*>(u)) {
                    Vehicle *veh = dynamic_cast<Vehicle*>(u);
                    if (veh->getVehicleType() == VehicleType::ARTILLERY) {
                        deltaLF -= safeCeil(veh->getAttackScore() * 0.5);
                    }
                }
            }
        }
    }else if(army->isARVNArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
    
            if(dis <= 3){
                if (dynamic_cast<Infantry*>(u)) {
                    Infantry *inf = dynamic_cast<Infantry*>(u);
                    if (inf->getInfantryType() == InfantryType::REGULARINFANTRY) {
                        double curAttackScore = inf->getAttackScore();
                        deltaEXP += safeCeil(curAttackScore + (3 * curAttackScore / (2 * dis)));  
                    }
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
// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    int deltaEXP = 0;
    int deltaLF = 0;
    if(army->isLiberationArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
            
        if(dis <= 2){
            if (dynamic_cast<Infantry*>(u)) {
                Infantry *inf = dynamic_cast<Infantry*>(u);
                deltaEXP -= safeCeil(inf->getAttackScore() * 0.2);          
            } else if (dynamic_cast<Vehicle*>(u)) {
                Vehicle *veh = dynamic_cast<Vehicle*>(u);
                deltaLF -= safeCeil(veh->getAttackScore() * 0.2); 
                }
            }
        }
    }else if(army->isARVNArmy()){
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);

            if(dis <= 2){
                if (dynamic_cast<Infantry*>(u)) {
                    Infantry *inf = dynamic_cast<Infantry*>(u);
                    deltaEXP += safeCeil(inf->getAttackScore() * 0.2); 
                } else if (dynamic_cast<Vehicle*>(u)) {
                    Vehicle *veh = dynamic_cast<Vehicle*>(u);
                    deltaLF += safeCeil(veh->getAttackScore() * 0.2); 
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
// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {
    if(army == nullptr){
        return;
    }
    for (Unit *u : army->getUnitList()->getUnits()) {
        double dis = calculateDistance(u->getCurrentPosition(), this->pos);

        if (dis <= 1) {
            // Đặt attackScore của các đơn vị quân sự (bộ binh, phương tiện) trong bán kính 1 đơn vị về 0
            if (dynamic_cast<Infantry*>(u)) {
                Infantry *inf = dynamic_cast<Infantry*>(u);
            } else if (dynamic_cast<Vehicle*>(u)) {
                Vehicle *vehicle = dynamic_cast<Vehicle*>(u);
            }
        }
    }
    army->setEXP(0);
    army->setLF(0);
}