#include "hcmcampaign.h"
//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
Position::Position(int r, int c) : r(r), c(c){}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { 
   this->r = r;
}
void Position::setCol(int c) { 
    this->c = c;
}
string Position::str() const {
    stringstream ss;
    ss << "(" << r << "," << c << ")";
    return ss.str();
}
Position::Position(const string &str_pos) {
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;
}
//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
Position Unit::getCurrentPosition() const {
    return this->pos;
}
void Unit::increaseQuantity(int q) {
    if (q > 0) quantity += q;
}
//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------
bool Infantry::isPerfectSquare(int a) const {
    int num = (int)sqrt(a);
    return (num * num == a) ? true : false;
}
int tong(int n) {
    if(n < 10)  return n;
    return (n % 10) + tong(n/10);
}
int Infantry::personalNumber(int num, int year) const {
    int perNum = tong(num) + tong(year);
    if(perNum < 10) return perNum;
    return personalNumber(perNum, 0);
}
int Infantry::getAttackScore() {
    return (modifiedScore != -1) ? modifiedScore : attackScore;
}
string Infantry::str() const {
    ostringstream oss;
    oss << "Infantry[infantryType=" << infantryTypeToString(getInfantryType()) 
        << ",quantity=" << quantity
        << ",weight=" << weight
        << ",position=" << pos.str()
        << "]";
    return oss.str();
}
//!----------------------------------------------
//! Lớp Vehicle
//!----------------------------------------------
string Vehicle::str() const {
    ostringstream oss;
    oss << "Vehicle[vehicleType=" << vehicleTypeToString(getVehicleType())
        << ",quantity=" << quantity
        << ",weight=" << weight
        << ",position=" << pos.str()
        << "]";

    return oss.str();
}
int Vehicle::getAttackScore() {
    if (modifiedScore != -1) {
        return modifiedScore;
    }
    return safeCeil((vehicleType * 304 + quantity * weight) / 30.0);
} 
//!----------------------------------------------
//! Lớp UnitList
//!----------------------------------------------
bool UnitList::isSpecial(int n) const {
    int bases[] = {3, 5, 7};
    for (int base : bases) {
        int sum = 0, power = 1;
        while (sum < n) {
            sum += power;
            if (sum == 0)
                return true;
            power *= base;
        }
    }
    return false;
}
UnitList::UnitList(int S) : count(0), head(nullptr), tail(nullptr) {
    capacity = (isSpecial(S)) ? 12 : 8;
}
UnitList::~UnitList() {
    Node *cur = head;
    while(cur){
        Node *temp = cur;
        cur =  cur->next;
        //delete temp->unit;
        delete temp;
    }
}
Unit* UnitList::findVehicle(VehicleType type){
    Node *cur = head;
    while(cur){
        Vehicle *v = dynamic_cast<Vehicle*>(cur->unit);
        if(v && v->getVehicleType() == type){
            return v;
        }
        cur = cur->next;
    }
    return nullptr;
}
Unit* UnitList::findInfantry(InfantryType type){
    Node *cur = head;
    while(cur){
        Infantry *i = dynamic_cast<Infantry*>(cur->unit);
        if(i && i->getInfantryType() == type){
            return i;
        }
        cur = cur->next;
    }
    return nullptr;
}
void UnitList::addUnit(Unit *u, bool &isInserted){
    if(count >= capacity)
        return;

    if(Infantry *i = dynamic_cast<Infantry*>(u)){
        Node *cur = head;
        while(cur){
        Infantry *found = dynamic_cast<Infantry*>(cur->unit);
        if(found && found->getInfantryType() == i->getInfantryType()){
            //found->increaseQuantity(i->getQuantity());
           // i->setQuantity(i->getQuantity());
           int totalQuantity = found->getQuantity() + i->getQuantity();
           int weight = found->getWeight();
            Position pos = found->getCurrentPosition();
            InfantryType type = i->getInfantryType();
   
           Infantry *merged = new Infantry(totalQuantity, weight, pos, type);
           Node* newNode = new Node(merged);
            
            newNode->prev = cur->prev;
            newNode->next = cur->next;
           
            if (cur->prev) cur->prev->next = newNode;
                else head = newNode;

            if (cur->next) cur->next->prev = newNode;
            else tail = newNode;

            remove(found);
            count++;

            isInserted = false;
           return;
        }
        cur = cur->next;
    }

    Node *newNode = new Node(i);
    newNode->next = head;
    newNode->prev = nullptr;
    
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode; // danh sách rỗng
    }
    head = newNode;
    count++;    
    isInserted = true;
    }else if(Vehicle *v = dynamic_cast<Vehicle*>(u)){
        Unit *found = findVehicle(v->getVehicleType());
        if(found){
            found->increaseQuantity(u->getQuantity());
           // v->setQuantity(v->getQuantity());
           isInserted = false;
            return;
        }

        Node *newNode = new Node(v);
        if(tail){
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }else{
            head = tail = newNode;
        }
        count++;
        isInserted = true;
    }
}
bool UnitList::insert(Unit *unit) {
   if (count >= capacity)
    return false;

    bool isInserted = false;
    addUnit(unit, isInserted);
    return isInserted;
}
void UnitList::insertToTail(Unit* unit) {
    Node* node = new Node(unit);
    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    count++;
}
bool UnitList::isContain(InfantryType infantryType) {
   return  findInfantry(infantryType) == nullptr ? false : true;
}
bool UnitList::isContain(VehicleType vehicleType) {
    return  findVehicle(vehicleType) == nullptr ? false : true;
}
string UnitList::str() const {
    ostringstream oss;
    oss << "UnitList[count_vehicle=" << countV()
        << ";count_infantry=" << countI();
    Node *cur = head;
    if (cur) {
        oss << ";";  
        while (cur) {
            oss << cur->unit->str();
            if (cur->next)
                oss << ",";
            cur = cur->next;
        }
    }
    oss << "]";
    return oss.str();
}
void UnitList::CheckAndRemove() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next; // lưu node tiếp theo trước khi remove
        if (cur->unit && cur->unit->getQuantity() <= 0) {
            removeNode(cur); // remove đã xử lý head, tail, prev/next, delete node
        }
        cur = next;
    }
}
int UnitList::countV() const {
    int result = 0;
    Node *cur = head;
    while (cur) {
        if (dynamic_cast<Vehicle*>(cur->unit)) {
            result++;
        }
        cur = cur->next;
    }
    return result;
}
int UnitList::countI() const {
    int result = 0;
    Node *cur = head;
    while (cur) {
        if (dynamic_cast<Infantry*>(cur->unit)) {
            result++;
        }
        cur = cur->next;
    }
    return result;
}
void UnitList::remove(Unit *unit) {
    Node* cur = head;
    while (cur) {
        if (cur->unit == unit) {
            removeNode(cur);
            return;
        }
        cur = cur->next;
    }
}
vector<Unit *> UnitList::getUnits() const{
    vector<Unit*> res;
    Node *cur = head;
    while(cur){
        res.push_back(cur->unit);
        cur = cur->next;
    }
    return res;
}
vector<Unit*> UnitList::getInfantryUnits() const{
    vector<Unit*> result;
    Node *cur = head;
    while (cur) {
        if (Infantry *i = dynamic_cast<Infantry*>(cur->unit)) {
            result.push_back(i); // lưu con trỏ Infantry
        }
        cur = cur->next;
    }
    return result;
}
vector<Unit*> UnitList::getVehicleUnits() const {
    vector<Unit*> result;
    Node *cur = head;
    while (cur) {
        if (Vehicle *v = dynamic_cast<Vehicle*>(cur->unit)) {
            result.push_back(v); // lưu con trỏ Vehicle
        }
        cur = cur->next;
    }
    return result;
}
void UnitList::removeNode(Node* node) {
    if (!node) return;

    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
    count--;
}
//!----------------------------------------------
//! Lớp Army
//!----------------------------------------------
Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : name(name),battleField(battleField) {
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
    if (unitList != nullptr) {
        delete unitList;
        unitList = nullptr;
    }
}
void Army::fight(Army* enemy, bool defense) {}
void Army::updateScore(bool update){
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
//!----------------------------------------------
//! CLASS LiberationArmy
//!----------------------------------------------
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
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField): Army(unitArray, size, name, battleField), unitArray(unitArray) {
    this->unitArray = new Unit*[size];
    size_V = 0;
    size_I = 0;

    for (int i = 0; i < size; ++i) {
        this->unitArray[i] = cloneUnit(unitArray[i]);  // Chỉ clone thôi
        if (dynamic_cast<Vehicle*>(unitArray[i])) size_V++;
        else if (dynamic_cast<Infantry*>(unitArray[i])) size_I++;
    }
    temp = new UnitList(size);
    //cout << "LiberationArmy constructor called\n";
}
LiberationArmy::~LiberationArmy() {
    for (int i = 0; i < size_V + size_I; ++i) {
        delete unitArray[i];  
    }
    delete[] unitArray;

    delete temp;
}
void LiberationArmy::fight(Army *enemy, bool defense){
    this->updateScore(false);
    enemy->updateScore(true);
   // cout << enemy->str() << endl;
    if(!defense){
        int nLF = safeCeil(getLF() * 1.5); 
        int nEXP = safeCeil(getEXP() * 1.5);

        // cout << "nLF " << nLF << endl;
        // cout << "nEXP " << nEXP << endl;
        // cout << "tan cong\n";

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
            // cout << "1" << endl;

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
            // cout << this->str() << endl;

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
                    // cout << "2" << endl;
                    // cout << "A" << endl;
                    for(Unit* u : subsetInfantry) {
                       // cout << u->str() << endl;
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
                    //cout << "2'\n";
                    for(Unit* u : this->getUnitList()->getUnits()){
                        u->setWeight(safeCeil(u->getWeight() - 0.1*(u->getWeight())));    
                    }                
                    this->getUnitList()->CheckAndRemove();
                }
        }else if(hasB && !hasA){
            
                if(nEXP > enemyEXP){ // 303 > 240
                   //cout << "3" << endl;
                    
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
        //cout << "Phong thu\n";
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
    ostringstream oss;
    oss << "LiberationArmy["
        << "LF=" <<  LF << ","
        << "EXP=" << EXP << ","
        << "unitList=" << unitList->str() 
        << ",battleField=" << (battleField ? battleField->str() : "")
        << "]";

        return oss.str();
}
int LiberationArmy::nearestFibonacci(int n) {
    if (n <= 0) return 1;  
    int a = 0, b = 1;
    while (b <= n) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}
void LiberationArmy::copyEnemyList(UnitList* enemyUnitList) {
    std::vector<Unit*> infantryList;
    std::vector<Unit*> vehicleList;

    for (Unit* u : enemyUnitList->getUnits()) {
        Unit* cloned = cloneUnit(u); // đảm bảo không ảnh hưởng đơn vị gốc
        if (dynamic_cast<Infantry*>(u)) {
            infantryList.push_back(cloned);
        } else if (dynamic_cast<Vehicle*>(u)) {
            vehicleList.push_back(cloned);
        }
    }

    for (Unit* inf : infantryList) {
        this->unitList->insertToTail(inf);
    }

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

//!----------------------------------------------
//! CLASS ARVN
//!----------------------------------------------
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
    ostringstream oss;
    oss << "ARVN["
        << "LF=" << LF << ","
        << "EXP=" << EXP << ","
        << "unitList=" << (unitList ? unitList->str() : "") 
        << ",battleField=" << (battleField != 0 ? battleField->str() : "")
        << "]";
    return oss.str();
}
//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp con
//!-----------------------------------------------------
TerrainElement::TerrainElement(Position pos, TerrainType terrainType) : pos(pos), terrain(terrainType){}
TerrainElement::~TerrainElement() {}
void Road::getEffect(Army *army) {
    //cout << "road\n";
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
    int deltaEXP1 = 0;
    int deltaLF1 = 0;
    int newEXP = 0;
    int newLF = 0;
        if(army->isLiberationArmy()){
            cout << "liber Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);
                //cout << dis << endl;
                if (dis <= 2.0) {
                    if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                        deltaEXP += safeCeil(inf->getAttackScore() * 1.3) - inf->getAttackScore(); 
                        //cout << "deltaEXP = " <<deltaEXP << endl;
                        inf->setAttackScore(safeCeil(inf->getAttackScore() * 1.3));
                    }else if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                        //cout << safeCeil(veh->getAttackScore() * 0.1) << endl;
                        double reduced = veh->getAttackScore() * 0.9;
                        int reducedScore = safeFloor(reduced);
                        cout << "deltaLF = " << veh->getAttackScore() - reducedScore << endl;
                        deltaLF -= veh->getAttackScore() - reducedScore;                       
                        cout << "deltaLF = " << deltaLF << endl;
                        veh->setAttackScore(reducedScore);
                        cout << "veh = " <<veh->getAttackScore() << endl;
                    }
                }
            }
            newEXP = army->getEXP() + deltaEXP;
            newLF = army->getLF()  + deltaLF;
        }else if(army->isARVNArmy()){
            cout << "Arvn Mountain Effect\n";
            for(Unit *u : army->getUnitList()->getUnits()){
                double dis = calculateDistance(u->getCurrentPosition(), this->pos);
                //cout << "dis = " << dis << endl;
            if (dis <= 4.0) {
                //cout << "dis = " << dis << endl;
                if (Infantry *inf = dynamic_cast<Infantry*>(u)) {
                    //cout << "newnew\n";
                    deltaEXP1 += safeCeil(inf->getAttackScore() * 1.2) - inf->getAttackScore();
                    inf->setAttackScore(safeCeil(inf->getAttackScore() * 1.2));
                }
                if (Vehicle *veh = dynamic_cast<Vehicle*>(u)) {
                    deltaLF1 -= veh->getAttackScore() - safeCeil(veh->getAttackScore() * 0.95);
                    veh->setAttackScore(safeCeil(veh->getAttackScore() * 0.95));
                }
            }
        }
       //cout << "deltaEXP1 = "<<deltaEXP1 << endl;
        newEXP = army->getEXP() + deltaEXP1;
        newLF = army->getLF()  + deltaLF1;
    }
    
    army->checkRange(newEXP, 500);
    army->checkRange(newLF, 1000);
    army->setEXP(newEXP);
    army->setLF(newLF);
}
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
    }else {
        for (Unit *u : army->getUnitList()->getUnits()) {
            double dis = calculateDistance(u->getCurrentPosition(), this->pos);
    
            if(dis <= 3.0){
                if (Infantry *inf = dynamic_cast<Infantry*>(u)) { 
                    if (inf->getInfantryType() == InfantryType::REGULARINFANTRY) {
                        cout << "dis = " << dis << endl;
                        // deltaEXP += safeCeil((3*inf->getAttackScore()) / (2 * dis));  
                        inf->setAttackScore(inf->getAttackScore() + safeCeil((3*inf->getAttackScore()) / (2 + dis)));
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
    }else{
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
//!----------------------------------------------
//! CLASS BattleField
//!---------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    terrain = new TerrainElement**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        terrain[i] = new TerrainElement*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            Position pos(i, j);
            TerrainElement* elem = nullptr;

            for (auto& p : arrayForest)
                if (p->getRow() == i && p->getCol() == j) { elem = new Mountain(pos); break; }

            if (!elem) for (auto& p : arrayRiver)
                if (p->getRow() == i && p->getCol() == j) { elem = new River(pos); break; }

            if (!elem) for (auto& p : arrayFortification)
                if (p->getRow() == i && p->getCol() == j) { elem = new Fortification(pos); break; }

            if (!elem) for (auto& p : arrayUrban)
                if (p->getRow() == i && p->getCol() == j) { elem = new Urban(pos); break; }

            if (!elem) for (auto& p : arraySpecialZone)
                if (p->getRow() == i && p->getCol() == j) { elem = new SpecialZone(pos); break; }

            
            if (!elem) elem = new Road(pos);

            terrain[i][j] = elem;
        }
    }
}
BattleField::~BattleField() {
    for(int i = 0; i < n_rows; ++i){
        for(int j = 0; j < n_cols; ++j){
            delete terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
}

TerrainElement* BattleField::getElement(int r, int c) const {
    if(r >= 0 && r < n_rows && c >= 0 && c < n_cols){
        return terrain[r][c];
    }
    return nullptr;
}
string BattleField::str() const {
    stringstream ss;
    ss << "BattleField[n_rows=" << n_rows << ",n_cols=" << n_cols << "]";

    // for (int i = 0; i < n_rows; ++i) {
    //     for (int j = 0; j < n_cols; ++j) {
    //         // Kiểm tra loại địa hình và in ra ký hiệu tương ứng
    //         TerrainElement* element = terrain[i][j];
    //         if (element != nullptr) {
    //             switch (element->getTerrain()) {
    //                 case ROAD: ss << "ROA"; break;
    //                 case MOUNTAIN: ss << "MOU"; break;
    //                 case RIVER: ss << "RIV"; break;
    //                 case FORTIFICATION: ss << "FOR"; break;
    //                 case URBAN: ss << "URB"; break;
    //                 case SPECIAL_ZONE: ss << "SPE"; break;
    //                 default: ss << "UNK"; break; // Trường hợp mặc định nếu không có loại địa hình nào
    //             }
    //         } else {
    //             ss << "UNK"; // Nếu phần tử địa hình là null
    //         }

    //         // Thêm dấu cách giữa các cột, trừ cột cuối
    //         if (j < n_cols - 1) {
    //             ss << ' ';
    //         }
    //     }

    //     // Thêm dấu xuống dòng giữa các hàng, trừ hàng cuối cùng
    //     if (i < n_rows - 1) {
    //         ss << '\n';
    //     }
    // }

    return ss.str();
}
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
Configuration::Configuration(const string &filepath){
    libUnits = nullptr;
    arvnUnits = nullptr;
    libsize = 0;
    ARVNsize = 0;

    TerrainType **battlefield = nullptr;
    vector<UNIT_NAME> units;
    int NUM_ROWS = 0, NUM_COLS = 0, EVENT_CODE = 0;

    processFile(filepath, battlefield, NUM_ROWS, NUM_COLS, units, EVENT_CODE);
        
    num_rows = NUM_ROWS;
    num_cols = NUM_COLS;
    eventCode = EVENT_CODE;

    this->libsize = 0;
    this->ARVNsize = 0;

    for(const auto &u : units){
        if(u.armyBelong == 0) libsize++;
        else if(u.armyBelong == 1) ARVNsize++;
    }

    libUnits = new Unit*[libsize];
    arvnUnits = new Unit*[ARVNsize];

    int lib_idx = 0, arvn_idx = 0;
    
    for(const auto &unit : units){
        if(isInfantryType(infantryTypeToString(unit.itype))){
            Position pos(unit.position_x, unit.position_y);
            Infantry *inf = new Infantry(unit.quantity, unit.weight, pos, unit.itype);
            if(unit.armyBelong == 0){
                libUnits[lib_idx++] = inf;
            }else{
                arvnUnits[arvn_idx++] = inf;
            }
        }else if(isVehicleType(vehicleTypeToString(unit.vtype))){
            Position pos(unit.position_x, unit.position_y);
            Vehicle *veh = new Vehicle(unit.quantity, unit.weight, pos, unit.vtype);
            if(unit.armyBelong == 0){
                libUnits[lib_idx++] = veh;
            }else{
                arvnUnits[arvn_idx++] = veh;
            }
        }
    }
    for(int i = 0; i < libsize; ++i){
        liberationUnits.push_back(libUnits[i]);
    }
    for(int j = 0; j < ARVNsize; ++j){
        ARVNUnits.push_back(arvnUnits[j]);
    }
}
vector<Position*> Configuration::parsePositions(const string &value) {
    vector<Position*> positions;
    size_t start = value.find('[');
    size_t end = value.find(']');
    if (start == string::npos || end == string::npos) return positions;

    string content = value.substr(start + 1, end - start - 1);
    string ncontent ="";
    for(int i = 0; i < content.length(); ++i){
        if(content[i] != ' ')
            ncontent += content[i];
    }
    stringstream ss(ncontent);
    string token;

    while (getline(ss, token, ')')) {
        size_t left = token.find('(');
        if (left != string::npos) {
            string coord = token.substr(left + 1);
            size_t comma = coord.find(',');
            if (comma != string::npos) {
                int x = stoi(coord.substr(0, comma));
                int y = stoi(coord.substr(comma + 1));
                positions.push_back(new Position(x, y));
            }
        }
    }
    return positions;
}

void Configuration::processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE)
{
    struct Data{
        string num_rows = "";
        string num_cols = "";
        string arr_forest = "";
        string arr_river = "";
        string arr_fortification = "";
        string arr_urban = "";
        string arr_special_zone = "";
        string event_code = "";
    };

    
    Data raw;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Not open this file \n";
    }

    string content, line;
    bool hasRow = false, hasCol = false;
    bool battlefieldInitialized = false; 

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        
        line = trim(line);
        
        size_t eq_pos = line.find('=');
        if (eq_pos == string::npos)
            continue;

        string key = line.substr(0, eq_pos);
        string value = line.substr(eq_pos + 1);
        
        if (key == "NUM_ROWS") {
            raw.num_rows = value;
        } else if (key == "NUM_COLS") {
            raw.num_cols = value;
        } else if (key == "EVENT_CODE") {
            raw.event_code = value;
        } else if(key == "ARRAY_FOREST"){
            raw.arr_forest = value;
        } else if(key == "ARRAY_RIVER"){
            raw.arr_river = value;        }
        else if(key == "ARRAY_FORTIFICATION"){
            raw.arr_fortification = value;        }
        else if(key == "ARRAY_URBAN"){
            raw.arr_urban = value;        }
        else if(key == "ARRAY_SPECIAL_ZONE"){
            raw.arr_special_zone = value;
        }else if(key == "UNIT_LIST"){
            string unit_list;
            size_t start_pos = value.find("[");
            size_t end_pos = value.find("]");

            if(start_pos != string::npos && end_pos == string::npos){
                unit_list += value.substr(start_pos + 1);

                while(getline(file, line)){
                    size_t close_pos = line.find("]");
                    
                    string cleanedLine;
                    for (char ch : line) {
                        if (ch != '\t') {
                            cleanedLine += ch;
                        }
                    }
                
                    if(close_pos != string::npos){
                        unit_list += cleanedLine.substr(0, close_pos);
                        break;
                    }
                    unit_list += cleanedLine;
                }                
                    value = unit_list;
            }else if(start_pos != string::npos && end_pos != string::npos){
                value = value.substr(start_pos + 1, end_pos - start_pos - 1);
            }
            //cout << value << endl;
            vector<string> Units;
            int n = value.length();
            int start = 0;
            int bracketCount = 0;

            for (int i = 0; i < n; ++i) {
                if (value[i] == '(') {
                    bracketCount++;
                } else if (value[i] == ')') {
                    bracketCount--;
                    if (bracketCount == 0) {
                        
                        Units.push_back(value.substr(start, i - start + 1));
                        
                        start = i + 2;
                    }
                }
            }
            for(int i  = 0; i < Units.size(); ++i){
                processUnit(Units[i], units);
            }
            }   
        
        if(raw.num_rows != ""){
            NUM_ROWS = stoi(raw.num_rows);
            hasRow = true;
        }
        if(raw.num_cols != ""){
            NUM_COLS = stoi(raw.num_cols);
            hasCol = true;
        }
        if (!battlefieldInitialized && hasRow && hasCol) {
            battlefield = new TerrainType*[NUM_ROWS];
            for (int i = 0; i < NUM_ROWS; ++i) {
                battlefield[i] = new TerrainType[NUM_COLS];
                for (int j = 0; j < NUM_COLS; ++j) {
                    battlefield[i][j] = ROAD;
                }
            }
            battlefieldInitialized = true;
        }
            if (raw.event_code != "")
        {
            EVENT_CODE = setEventCode(stoi(raw.event_code));
        }
        if(raw.arr_forest != ""){
            arrayForest = parsePositions(raw.arr_forest);
        }
        if(raw.arr_river != ""){
            arrayRiver = parsePositions(raw.arr_river);
        }
        if(raw.arr_fortification != ""){
            arrayFortification = parsePositions(raw.arr_fortification);
        }
        if(raw.arr_urban!= ""){
            arrayUrban = parsePositions(raw.arr_urban);
        }
        if(raw.arr_special_zone != ""){
            arraySpecialZone = parsePositions(raw.arr_special_zone);
        }
    }
file.close();
}
string Configuration::print_battlefield(const TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS){
    stringstream ss;

    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
        {
            switch(battlefield[i][j]) {
    case ROAD: ss << "ROA"; break;
    case MOUNTAIN: ss << "MOU"; break;
    case RIVER: ss << "RIV"; break;
    case FORTIFICATION: ss << "FOR"; break;
    case URBAN: ss << "URB"; break;
    case SPECIAL_ZONE: ss << "SPE"; break;
}
            if (j < NUM_COLS - 1)
            ss << ' ';
        }
        if(i < NUM_ROWS - 1)
        ss << '\n';
    }
        return ss.str();
}
string Configuration::print_UNIT_NAME(const vector<UNIT_NAME> &units) {
    stringstream ss;
    ss << "[\n";
    for (size_t i = 0; i < units.size(); ++i)
    {
        const auto &unit = units[i];
        if(isInfantryType(infantryTypeToString(unit.itype)) == true)
            ss << infantryTypeToString(unit.itype) << "(";
        else if(isVehicleType(vehicleTypeToString(unit.vtype)) == true) 
            ss << vehicleTypeToString(unit.vtype) << "(";

        ss << unit.quantity << ","
            << unit.weight << ","
            << "(" << unit.position_x << "," << unit.position_y << "),"
            << unit.armyBelong << ")";

        if (i != units.size() - 1)
            ss << ",\n";
    }
    ss << "\n]";

    return ss.str();
}
void Configuration::clearBattlefield(TerrainType **&battlefield, const int &NUM_ROWS, const int &NUM_COLS) {
    if(battlefield != nullptr){
        for (int i = 0; i < NUM_ROWS; ++i)
        {
            delete[] battlefield[i];
        }
        delete[] battlefield;
        battlefield = nullptr;
        }
}

void Configuration::processUnit(const string &unit_str, vector<UNIT_NAME> &units) {
    size_t openParen = unit_str.find("(");
    size_t closeParen = unit_str.rfind(")");
    
    if (openParen == string::npos || closeParen == string::npos)    
        return;

    string type = unit_str.substr(0, openParen);
    string inside = unit_str.substr(openParen + 1, closeParen - openParen - 1); // bỏ () ra

    stringstream ss(inside);
    string quantity, weight, pos, army;

    getline(ss, quantity, ',');
    getline(ss, weight, ',');
    getline(ss, pos, ')'); // lấy "(x,y"
    
    if(ss.peek() == ',')
    ss.ignore(1); // bỏ dấu ,

    getline(ss, army);

    size_t comma = pos.find(',');
    string x = pos.substr(1, comma - 1); // pos[1] tới comma
    string y = pos.substr(comma + 1);

    UNIT_NAME u;
    u.quantity = stoi(quantity);
    u.weight = stoi(weight);
    u.position_x = stoi(x);
    u.position_y = stoi(y);
    u.armyBelong = stoi(army);
if(isInfantryType(type))
{
    if(type == "SNIPER") u.itype = SNIPER;
    else if (type == "MORTARSQUAD") u.itype = MORTARSQUAD;
    else if (type == "ANTIAIRCRAFTSQUAD") u.itype = ANTIAIRCRAFTSQUAD;
    else if (type == "ENGINEER") u.itype = ENGINEER;
    else if (type == "SPECIALFORCES") u.itype = SPECIALFORCES;
    else if (type == "REGULARINFANTRY") u.itype = REGULARINFANTRY;
}else if(isVehicleType(type)){
    if(type == "TRUCK") u.vtype = TRUCK;
    else if (type == "MORTAR") u.vtype = MORTAR;
    else if (type == "ANTIAIRCRAFT") u.vtype = ANTIAIRCRAFT;
    else if (type == "ARMOREDCAR") u.vtype = ARMOREDCAR;
    else if (type == "APC") u.vtype = APC;
    else if (type == "ARTILLERY") u.vtype = ARTILLERY;
    else if(type == "TANK") u.vtype = TANK;
}
    units.push_back(u);
}
bool Configuration::isVehicleType(const string &type)
{
    return type == "TRUCK" || type == "MORTAR" || type == "ANTIAIRCRAFT" ||
            type == "ARMOREDCAR" || type == "APC" || type == "ARTILLERY" ||
            type == "TANK";
}

bool Configuration::isInfantryType(const string &type)
{
    return type == "SNIPER" || type == "ANTIAIRCRAFTSQUAD" || type == "MORTARSQUAD" ||
            type == "ENGINEER" || type == "SPECIALFORCES" || type == "REGULARINFANTRY";
}
Configuration::~Configuration(){
    for (Position* p : arrayForest) {
        delete p;
    }
    for (Position* p : arrayRiver) {
        delete p;
    }
    for (Position* p : arrayFortification) {
        delete p;
    }
    for (Position* p : arrayUrban) {
        delete p;
    }
    for (Position* p : arraySpecialZone) {
        delete p;
    }

    arrayForest.clear();
    arrayRiver.clear();
    arrayFortification.clear();
    arrayUrban.clear();
    arraySpecialZone.clear();

    if (libUnits != nullptr) {
        for (int i = 0; i < libsize; ++i) {
            delete libUnits[i];
        }
        delete[] libUnits;
        libUnits = nullptr;
    }

    if (arvnUnits != nullptr) {
        for (int i = 0; i < ARVNsize; ++i) {
            delete arvnUnits[i];
        }
        delete[] arvnUnits;
        arvnUnits = nullptr;
    }
}

string Configuration::str() const{
stringstream ss;
ss  << "[num_rows=" << num_rows
    << ",num_cols=" << num_cols << ",";
    
    auto printPositionArr = [](const vector<Position*> &arr){
        stringstream out;
        out << "[";
        for(size_t i = 0; i < arr.size(); ++i){
            out << arr[i]->str();
            if(i != arr.size() - 1)
                out << ",";
        }
        out << "]";
        return out.str();
    };
    
    ss << "arrayForest=" << printPositionArr(arrayForest) << ",";
    ss << "arrayRiver=" << printPositionArr(arrayRiver) << ",";
    ss << "arrayFortification=" << printPositionArr(arrayFortification) << ",";
    ss << "arrayUrban=" << printPositionArr(arrayUrban) << ",";
    ss << "arraySpecialZone=" << printPositionArr(arraySpecialZone) << ",";

    ss << "liberationUnits=["; 
    for (int i = 0; i < libsize; ++i) {
        if (liberationUnits[i]) {
            ss << liberationUnits[i]->str();
            if (i != libsize - 1)
                ss << ",";
        }
    }
        ss << "],";

    ss << "ARVNUnits=["; 
    for (int i = 0; i < ARVNsize; ++i) {
        if (ARVNUnits[i]) {
            ss << ARVNUnits[i]->str();
            if (i != ARVNsize - 1)
                ss << ",";
        }
    }
    ss << "],";

    ss << "eventCode=" << eventCode << "]";
    return ss.str();
}
int Configuration::setEventCode(int code){
    if(code >= 100){
        return code % 100;
    }else if(code < 0){
        return 0;
    }else {return code;}
}
//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
HCMCampaign::HCMCampaign(const string &config_file_path){
    config = new Configuration(config_file_path);
    battleField = new BattleField(
        config->getNumRows(),
        config->getNumCols(),
        config->getForestPositions(),
        config->getRiverPositions(),
        config->getFortificationPositions(),
        config->getUrbanPositions(),
        config->getSpecialZonePositions()
    );
    
    vector<Unit*> liberUnits = config->getLiberationUnits();
    Unit** uniArr = new Unit*[liberUnits.size()];
    for(int i = 0; i <liberUnits.size(); ++i){
        uniArr[i] = liberUnits[i];
    }
    liberationArmy = new LiberationArmy(uniArr, (config->getLiberationUnits()).size(), "LiberationArmy", battleField);
    delete[] uniArr;
    
    vector<Unit*> arvnUnits = config->getARVNUnits();
    Unit** uniArr1 = new Unit*[arvnUnits.size()];
    for(int i = 0; i < arvnUnits.size(); ++i){
        uniArr1[i] = arvnUnits[i];
    }
    arvnArmy = new ARVN(uniArr1, (config->getARVNUnits()).size(), "ARVN", battleField);
    delete[] uniArr1;
}
void HCMCampaign::run(){
int eventCode = config->getEventCode();

if(eventCode < 75){
    liberationArmy->fight(arvnArmy, false);

    if(arvnArmy->getLF() > 0){
        liberationArmy->fight(arvnArmy, true);
    }
}else{
    arvnArmy->fight(liberationArmy, true);  // true để tấn công

    if (liberationArmy->getLF() > 0) {
        liberationArmy->fight(arvnArmy, false);  // false để phòng thủ
        }
    }
}
string HCMCampaign::printResult() {
return "LIBERATIONARMY[LF=" + to_string(liberationArmy->getLF()) + ",EXP=" + to_string(liberationArmy->getEXP()) + "]" +
        "-ARVN[LF=" + to_string(arvnArmy->getLF()) + ",EXP=" + to_string(arvnArmy->getEXP()) + "]";
}
void HCMCampaign::remove(Army *army){
vector<Unit*> units = army->getUnitList()->getUnits();
for (auto it = units.begin(); it != units.end(); ) {
    if ((*it)->getAttackScore() <= 5) {
            army->getUnitList()->remove(*it);
    } else {
            ++it;
        }
    }
}
HCMCampaign::~HCMCampaign() {
    delete config;
    delete battleField;
    delete liberationArmy;
    delete arvnArmy;
}