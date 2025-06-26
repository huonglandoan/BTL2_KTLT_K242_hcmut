#include "LiberationArmy.h"

// TODO: Implement
// class LiberationArmy
int  LiberationArmy::minSubsetSumGreaterThan(const vector<Unit*>& units, int target) {
    int n = units.size();
    int min_sum = INT_MAX;
   

    for (int mask = 1; mask < (1 << n); ++mask) {
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += units[i]->getAttackScore();
            }
        }

        if (sum > target && sum < min_sum) {
            min_sum = sum;
        }
    }

    return (min_sum == INT_MAX) ? -1 : min_sum;
    
}
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name): Army(unitArray,size,name) {
    this->unitArray = new Unit*[size];
    size_V = 0;
    size_I = 0;

    for (int i = 0; i < size; ++i) {
        this->unitArray[i] = cloneUnit(unitArray[i]);  // Chỉ clone thôi
        if (dynamic_cast<Vehicle*>(unitArray[i])) size_V++;
        else if (dynamic_cast<Infantry*>(unitArray[i])) size_I++;
    }
    temp = new UnitList(size);
  //  cout << "LiberationArmy constructor called\n";
}
LiberationArmy::~LiberationArmy() {
    for (int i = 0; i < size_V + size_I; ++i) {
        delete unitArray[i];  // Chỉ xóa những gì mình clone
    }
    delete[] unitArray;

    delete temp;
}
void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
    this->updateScore(false);
    enemy->updateScore(true);
   // cout << enemy->str() << endl;
    

    if(!defense){
        int nLF = safeCeil(getLF() * 1.5); 
        int nEXP = safeCeil(getEXP() * 1.5);

        // cout << "nLF " << nLF << endl;
        // cout << "nEXP " << nEXP << endl;
        
        int enemyLF = enemy->getLF();
        int enemyEXP = enemy->getEXP();
        
        vector<Unit*> myinfantryUnits = this->getUnitList()->getInfantryUnits();
        vector<Unit*> myvehicleUnits = this->getUnitList()->getVehicleUnits();
    
        int minInfantrySum = minSubsetSumGreaterThan(myinfantryUnits, enemyEXP);
        int minVehicleSum = minSubsetSumGreaterThan(myvehicleUnits, enemyLF);
    
        vector<Unit*> subsetInfantry;
        vector<Unit*> subsetVehicle;
    
        if (minInfantrySum != -1)
            subsetInfantry = selectMinSubset(myinfantryUnits, enemyEXP);
        if (minVehicleSum != -1)
            subsetVehicle = selectMinSubset(myvehicleUnits, enemyLF);
    
    
        bool hasA = !subsetInfantry.empty();
        bool hasB = !subsetVehicle.empty();
        bool win = false;
        
        if(hasA && hasB){
            cout << "1" << endl;

            for(Unit* u : subsetInfantry) this->getUnitList()->remove(u);
            for(Unit* u : subsetVehicle) this->getUnitList()->remove(u);

            vector<Unit*> ICaptured;
            vector<Unit*> VCaptured;

            for(Unit* u : this->getUnitList()->getUnits()) {
                if(Infantry *inf = dynamic_cast<Infantry*>(u)){
                    ICaptured.push_back(cloneUnit(u));
                    this->getUnitList()->remove(u);
                }else{
                    VCaptured.push_back(cloneUnit(u));
                    this->getUnitList()->remove(u);
                }
            }
            
            for(int i = (int)ICaptured.size() - 1; i >= 0; --i)
                this->getUnitList()->insert(ICaptured[i]);

            for(Unit *u : VCaptured){
                this->getUnitList()->insert(u);
            }

            this->getUnitList()->CheckAndRemove();

            for(Unit* u : enemy->getUnitList()->getUnits()){
                temp->insert(cloneUnit(u));
                enemy->getUnitList()->remove(u);
            }   
            cout << this->str() << endl;

            std::vector<Unit*> infantryCaptured;
            std::vector<Unit*> vehicleCaptured;

            for (Unit* u : temp->getUnits()) {
                if (dynamic_cast<Infantry*>(u)) {
                    infantryCaptured.push_back(u);
                } else {
                    vehicleCaptured.push_back(u);
                }
            }
            
            for (Unit* u : infantryCaptured) {
                this->getUnitList()->insert(cloneUnit(u));
            }

            for (int i = (int)vehicleCaptured.size() - 1; i >= 0; --i) {
                this->getUnitList()->insert(cloneUnit(vehicleCaptured[i]));
            }

            this->updateScore(true);
            enemy->updateScore(true);
            enemy->markAsDefeated();
        } else if(hasA && !hasB){
            
                if(nLF > enemyLF){
                    cout << "2" << endl;
                    cout << "A" << endl;
                    for(Unit* u : subsetInfantry) {
                        this->getUnitList()->remove(u);
                    }
                    vector<Unit*> toRemove;
                    for(Unit* u : this->getUnitList()->getUnits()){
                        if (dynamic_cast<Vehicle*>(u)) {
                            toRemove.push_back(u);
                        }
                    }
                    for (Unit* u : toRemove) {
                        this->getUnitList()->remove(u);
                    }
                    this->getUnitList()->CheckAndRemove();

                   // cout << this->str() << endl;

                    for(Unit* u : enemy->getUnitList()->getUnits()){
                        temp->insert(cloneUnit(u));
                        enemy->getUnitList()->remove(u);
                    }

                    for(Unit*u : temp->getUnits()){
                        this->getUnitList()->insert(cloneUnit(u));
                    }
                    //cout << this->str() << "last"<< endl;

                    this->updateScore(true);
                    enemy->updateScore(true);
                    enemy->markAsDefeated();
                }else{
                    for(Unit* u : this->getUnitList()->getUnits()){
                        u->setWeight(safeCeil(u->getWeight() - 0.1*(u->getWeight())));    
                    }                
                    this->getUnitList()->CheckAndRemove();
                }
        }else if(hasB && !hasA){
           // cout << "3" << endl;
            
                if(nEXP > enemyEXP){ // 303 > 240
                  //  cout << "3" << endl;
                    
                    for(Unit* u : this->getUnitList()->getUnits()) this->getUnitList()->remove(u);
                    this->getUnitList()->CheckAndRemove();

                    for(Unit* u : enemy->getUnitList()->getUnits()){
                        temp->insert(cloneUnit(u));
                        enemy->getUnitList()->remove(u);
                    }

                    for(Unit*u : temp->getUnits()){
                        this->getUnitList()->insert(cloneUnit(u));
                    }

                    // cout << enemy->str() << endl;
                    // cout << this->str() << endl;

                    this->updateScore(true);
                    enemy->updateScore(true);
                    // cout << enemy->str() << endl;
                    // cout << this->str() << endl;
                    enemy->markAsDefeated();    
                }else{
                    //cout << "3'" << endl;
                    for(Unit* u : this->getUnitList()->getUnits()){
                        u->setWeight(safeCeil(u->getWeight() - 0.1*u->getWeight()));                  
                    }
                this->getUnitList()->CheckAndRemove();
            }
        }else if(!hasA && !hasB){
            //cout << "4" << endl;
            for(Unit* u : this->getUnitList()->getUnits()){
                u->setWeight(safeCeil(u->getWeight()*0.9));        
            }
            //cout << this->str() << endl;
            this->getUnitList()->CheckAndRemove();

            this->updateScore(true);
            enemy->updateScore(true);
        }
    }else if(defense){
        this->updateScore(false);
        enemy->updateScore(true);

        int nLF = safeCeil(this->getLF() * 1.3); 
        int nEXP = safeCeil(this->getEXP() * 1.3);

        checkRange(nLF, 1000);
        checkRange(nEXP, 500);

        int enemyLF = enemy->getLF();
        int enemyEXP = enemy->getEXP();

        if(nLF > enemyLF && nEXP > enemyEXP){
            this->setLF(nLF);
            this->setEXP(nEXP);
        }else if(this->getLF() <= enemyLF && this->getEXP() <= enemyEXP){
            while(this->getLF() <= enemyLF && this->getEXP() <= enemyEXP){
                for (Unit *u : this->getUnitList()->getUnits()) {
                    int currentQty = u->getQuantity();
                    int nextFib = nearestFibonacci(currentQty);
                    // Nếu quantity hiện tại ĐÃ LÀ Fibonacci rồi, thì cần nhảy lên Fibonacci tiếp theo
                    u->setQuantity(nextFib);
                }
                this->updateScore(true);
            } 
        }else{
            for(Unit *u : this->getUnitList()->getUnits()){
                int reducedQty = safeCeil(u->getQuantity()*0.9);
                u->setQuantity(reducedQty);
            }
            this->getUnitList()->CheckAndRemove();
            this->updateScore(true);
        }
    }
}


string LiberationArmy::str() const {
    // TODO: Implement
    ostringstream oss;
    oss << "LiberationArmy["
        << "LF=" <<  LF << ","
        << "EXP=" << EXP << ","
        << "unitList=" << unitList->str() 
        //<< ",battleField=" << (battleField ? battleField->str() : "")
        << "]";

        return oss.str();
}


// Sup function
int LiberationArmy::nearestFibonacci(int n) {
    if (n <= 0) return 1;  // Số Fibonacci đầu tiên là 1

    int a = 0, b = 1;

    // Tìm số Fibonacci lớn nhất nhỏ hơn hoặc bằng n
    while (b <= n) {
        int temp = b;
        b = a + b;
        a = temp;
    }

    // Trả về số Fibonacci tiếp theo (số lớn hơn n)
    return b;
}


void LiberationArmy::copyEnemyList(UnitList* enemyUnitList) {
    std::vector<Unit*> infantryList;
    std::vector<Unit*> vehicleList;

    // Phân loại đơn vị enemy
    for (Unit* u : enemyUnitList->getUnits()) {
        Unit* cloned = cloneUnit(u); // đảm bảo không ảnh hưởng đơn vị gốc
        if (dynamic_cast<Infantry*>(u)) {
            infantryList.push_back(cloned);
        } else if (dynamic_cast<Vehicle*>(u)) {
            vehicleList.push_back(cloned);
        }
    }

    // Thêm theo thứ tự: Infantry trước
    for (Unit* inf : infantryList) {
        this->unitList->insertToTail(inf);
    }

    // Sau đó Vehicle
    for (Unit* v : vehicleList) {
        this->unitList->insertToTail(v);
    }
}


std::vector<Unit*> LiberationArmy::selectMinSubset(const std::vector<Unit*>& units, int target) {
    int n = units.size();
    int min_sum = INT_MAX;
    int best_mask = 0;

    for (int mask = 1; mask < (1 << n); ++mask) {
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += units[i]->getAttackScore();
            }
        }

        if (sum > target && sum < min_sum) {
            min_sum = sum;
            best_mask = mask;
        }
    }

    std::vector<Unit*> result;
    if (min_sum == INT_MAX) return result; // không tìm được tổ hợp phù hợp

    for (int i = 0; i < n; ++i) {
        if (best_mask & (1 << i)) {
            result.push_back(units[i]);
        }
    }

    return result;
}
