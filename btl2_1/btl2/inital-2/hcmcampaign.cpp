#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////

string infantryTypeToString(InfantryType type){
    switch(type){
        case SNIPER: return "SNIPER";
        case ANTIAIRCRAFTSQUAD: return "ANTIAIRCRAFTSQUAD";
        case MORTARSQUAD: return "MORTARSQUAD";
        case ENGINEER: return "ENGINEER";
        case SPECIALFORCES: return "SPECIALFORCES";
        case REGULARINFANTRY: return "REGULARINFANTRY";
        default: return "UNKNOWN";
    }
}

bool Infantry::isPerfectSquare(int a) const
{
    int num = (int)sqrt(a);
    return (num * num == a) ? true : false;
}
int tong(int n) {
    if(n < 10)  return n;
    return (n % 10) + tong(n/10);
}
int Infantry::personalNumber(int num, int year) const
{
    int perNum = tong(num) + tong(year);
    if(perNum < 10) return perNum;
    return personalNumber(perNum, 0);
}
int Infantry::getAttackScore()
{
    int score = static_cast<int>(infantryType) * 56 + quantity * weight;

    if (infantryType == SPECIALFORCES && isPerfectSquare(weight))
       { 
        score += 75;
        return score;
        }

    int perNum = personalNumber(score, 1975);

    if (perNum > 7){
        if(quantity == 1) quantity += static_cast<int>(ceil(quantity * 0.2));
        else quantity += static_cast<int>(round(quantity * 0.2));
    }else if (perNum < 3 && quantity > 1){
        if(quantity == 1) quantity -= static_cast<int>(ceil(quantity * 0.1));
        else quantity -= static_cast<int>(round(quantity * 0.1));
    }
    double rawScore = static_cast<int>(infantryType) * 56 + quantity * weight;
    return static_cast<int>(round(rawScore));
}
string Infantry::str() const
{
    ostringstream oss;
    oss << "Infantry[infantryType=" << infantryTypeToString(getInfantryType()) 
        << ",quantity=" << quantity
        << ",weight=" << weight
        << ",position=" << pos.str()
        << "]";
    return oss.str();
}
Position::Position(const string &str_pos)
{
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;

}
Unit::~Unit() // xem lai co can thiet khong
{
    quantity = 0;
    weight = 0;
    pos = Position(0, 0);
}
void Unit::setWeight(int weight) {
    this->weight = weight;
}

void Unit::setQuantity(int quantity) {
    this->quantity = quantity;
}
Position Unit::getCurrentPosition() const
{
    return this->pos;
}
int Vehicle::getAttackScore() {
    return static_cast<int>(ceil((vehicleType * 304 + quantity * weight) / 30.0));

} 

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

bool UnitList::isSpecial(int n) const
{
    int bases[] = {3, 5, 7};
    for (int base : bases)
    {
        int sum = 0, power = 1;
        while (sum < n)
        {
            sum += power;
            if (sum == 0)
                return true;
            power *= base;
        }
    }
    return false;
}
UnitList::UnitList(int S) : countInfantry(0), countVehicle(0), count(0), head(nullptr), tail(nullptr)
{
    // TODO: Implement
    capacity = (isSpecial(S)) ? 12 : 8;
}
UnitList::~UnitList() {
    Node *cur = head;
    while(cur){
        Node *temp = cur;
        cur =  cur->next;
        delete cur;
    }
}
bool UnitList::insert(Unit *unit)
{
    if (unit == nullptr || count >= capacity)   
        return false;

    Node *newNode = new Node(unit);

    if(dynamic_cast<Vehicle*>(unit)){
        countVehicle++;
        if(!head){
        head = tail = newNode;
    } else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    } else if(dynamic_cast<Infantry*>(unit)){
        countInfantry++;
        
        if(!head){
            head = tail = newNode; 
        }else {
            newNode->next = head; 
            head->prev = newNode;
            head = newNode;
        }
    }else{
        delete newNode;
        return false;
    }
    count++;
    return true;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    // TODO: Implement
    Node *cur = tail;
    while(cur){
        Vehicle* v = dynamic_cast<Vehicle*>(cur->unit);
        if(v && v->getVehicleType() == vehicleType)
            return true;
        cur = cur->prev;
    }
   return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    // TODO: Implementå
    Node *cur = head;
    while(cur){
        Infantry *i = dynamic_cast<Infantry*>(cur->unit);
        if(i && i->getInfantryType() == infantryType)
            return true;
        cur = cur->next;
    }
    return false;
}

string UnitList::str() const
{
    ostringstream oss;
    oss << "UnitList[count_vehicle=" << countVehicle
        << ";count_infantry=" << countInfantry;

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

void UnitList::remove(Unit *unit) {
    // TODO: Implement
    if(!unit || !head)
        return;

    Node *cur = head;
    while(cur){
        if(cur->unit == unit){
            if(cur == head) {
                head = cur->next;
                if(head){
                    head->prev = nullptr;
                }
            }

            if(cur == tail) {
                tail = cur->prev;
                if(tail){
                    tail->next = nullptr;
                }
            
            if(cur->prev){
                cur->prev->next = cur->next;
            }
            if(cur->next){
                cur->next->prev = cur->prev;
            }

            if(dynamic_cast<Vehicle*>(unit)){
                countVehicle--;
            }else if(dynamic_cast<Infantry*>(unit)){
                countInfantry--;
            }

            count--;
        }
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
    vector<Unit*> res;
    Node *cur = head;
    while(cur){
        if(dynamic_cast<Infantry*>(cur->unit))
            res.push_back(cur->unit);
        cur = cur->next;
    }

    sort(res.begin(), res.end(), [](Unit* a, Unit* b) {
        return a->getAttackScore() < b->getAttackScore(); // sua lai
    });

    return res;
}

vector<Unit*> UnitList::getVehicleUnits() const {
    vector<Unit*> res;
    Node *cur = tail;
    while(cur){
        if(dynamic_cast<Vehicle*>(cur->unit))
            res.push_back(cur->unit);
        cur = cur->prev;
    }
    sort(res.begin(), res.end(), [](Unit* a, Unit* b) {
        return a->getAttackScore() < b->getAttackScore(); // sua lai
    });

    return res;
}


LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name)
                                                : Army(unitArray,size,name) {                                                       
    // TODO: Implement
   this->unitArray = unitArray;
   size_V = unitList->countV();
   size_I = unitList->countI();
}
// LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, bool check)
//                                                 : Army(unitArray,size,name) {                                                       
//     // TODO: Implement
//    this->unitArray = unitArray;
//    size_V = unitList->countV();
//    size_I = unitList->countI();
// }
void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
    this->updateScore(false);
    enemy->updateScore(true);

    if(!defense){
        double nLF = this->LF * 1.5; 
        double nEXP = this->EXP * 1.5;
        double enemyLF = enemy->getLF();
        double enemyEXP = enemy->getEXP();
        
        vector<Unit*> myInfantry = this->getUnitList()->getInfantryUnits();
        vector<Unit*> myVehicle = this->getUnitList()->getVehicleUnits();
        vector<Unit*> enemyInfantry = enemy->getUnitList()->getInfantryUnits();
        vector<Unit*> enemyVehicle = enemy->getUnitList()->getVehicleUnits();

       
        vector<Unit*> A, B;
       
        int sumA = knapsackSubset(myInfantry, enemyEXP, A);
        int sumB = knapsackSubset(myVehicle, enemyLF, B);
        
        for(Unit* u : A) {
            cout << u->str() << endl;
            cout << u->getAttackScore() << endl;}
        for(Unit* u : B) {
            cout << u->str() << endl;
            cout << u->getAttackScore() << endl;}
            
       bool hasA = !A.empty() && sumA > enemyEXP;
       bool hasB = !B.empty() && sumB > enemyLF;

        if(hasA && hasB){
            
            for(Unit* u : A) this->getUnitList()->remove(u);
            for(Unit* u : B) this->getUnitList()->remove(u);

            for(Unit* u : enemyInfantry)
                this->getUnitList()->insert(cloneUnit(u));
            
            for(Unit* u : enemyVehicle)
                this->getUnitList()->insert(cloneUnit(u));
       
            this->updateScore(false);
            enemy->markAsDefeated();
        }
        else if(hasA || hasB){
            if(hasA && !hasB){
                if(nLF > enemyLF){
                    for(Unit* u : A) 
                        this->getUnitList()->remove(u);
                    for(Unit *u : B)
                        this->getUnitList()->remove(u);
                    this->updateScore(false);

                    for(Unit* u : enemyInfantry)
                        this->getUnitList()->insert(cloneUnit(u));
                    for(Unit* u: enemyVehicle)
                        this->getUnitList()->insert(cloneUnit(u));

                        enemy->markAsDefeated();
                }
            }else if(hasB && !hasA){
                if(nEXP > enemyEXP){
                    for(Unit *u : B)
                        this->getUnitList()->remove(u);
                    for(Unit *u : A)
                        this->getUnitList()->remove(u);
                    this->updateScore(false);
                        
                    for(Unit* u : enemyInfantry)
                        this->getUnitList()->insert(cloneUnit(u));
                    for(Unit* u: enemyVehicle)
                        this->getUnitList()->insert(cloneUnit(u));

                        enemy->markAsDefeated();
                }
            }
        }else{
            for(Unit* u : this->getUnitList()->getUnits()){
                u->setWeight(static_cast<int>(u->getWeight() * 0.9)); 
            }
        }
    }else if(defense){
        double nLF = this->LF * 1.3; 
        double nEXP = this->EXP * 1.3;
        double enemyLF = enemy->getLF();
        double enemyEXP = enemy->getEXP();

        if(nLF > enemyLF && nEXP > enemyEXP){
            // for(Unit* u : this->getUnitList()->getUnits())
            //         this->getUnitList()->remove(u);
            
            for(Unit* u : enemy->getUnitList()->getUnits())
                this->getUnitList()->insert(cloneUnit(u));

            this->updateScore(false);
        }else if(nLF <= enemyLF && nEXP <= enemyEXP){
            for(Unit *u : this->getUnitList()->getUnits()){
                u->setQuantity(u->getQuantity() + nearestFibonacci(u->getQuantity()));
            }
        }else{
            for(Unit *u : this->getUnitList()->getUnits()){
                int reducedQty = safeCeil(u->getQuantity()*0.9);
                u->setQuantity(reducedQty);
            }
        }
    }
this->updateScore(true);
enemy->updateScore(true);
}

string LiberationArmy::str() const {
    // TODO: Implement
    ostringstream oss;
    oss << "LiberationArmy["
        << "LF=" <<  LF << ","
        << "EXP=" << EXP << ","
        << "unitList=" << unitList->str() 
        //<< "battleField=" << (battleField ? battleField->getName() : "null")
        << "]";

        return oss.str();
}


// Sup function
int LiberationArmy::nearestFibonacci(int value) {
    // TODO: Implement
    int a = 0; 
    int b = 1;
    while(b < value) {
        int temp = a;
        a = b;
        b = temp + b;
    }

    if(abs(b - value) < abs(a - value))
        return b;

    return a;
}



Unit* LiberationArmy::cloneUnit(Unit* unit) {
    // TODO: Implement
   if(Infantry *inf = dynamic_cast<Infantry*>(unit)){
    return new Infantry(*inf);
   } else if(Vehicle *veh = dynamic_cast<Vehicle*>(unit)){
    return new Vehicle(*veh);
   } 
   return nullptr;
}

int  LiberationArmy::knapsackSubset(vector<Unit*>& units, int target, vector<Unit*>& result) {
    int maxScore = 0;
   
    for (Unit* u : units) {
        maxScore += u->getAttackScore();
    }

    vector<int> dp(maxScore + 1, INT_MAX);
    vector<vector<Unit*>> selected(maxScore + 1);  

    dp[0] = 0;  
    // Duyệt qua từng unit và cập nhật dp
    for (Unit* u : units) {
        int score = u->getAttackScore();
        for (int i = maxScore; i >= score; --i) {
            if (dp[i - score] != INT_MAX && dp[i] > dp[i - score] + 1) {
                dp[i] = dp[i - score] + 1;
                selected[i] = selected[i - score];  
                selected[i].push_back(u);  
        }
    }
}
    for (int i = target + 1; i <= maxScore; ++i) {
        if (dp[i] != INT_MAX) {
            result = selected[i];  
            return i;  
        }
    }
    return -1; 
}

ARVN::ARVN(Unit** unitArray, int size, string name)
    : Army(unitArray, size, name) {
        // TODO: Implement
}

void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
    if(!defense){
        for(Unit *u : this->getUnitList()->getUnits()){
            int newQuantity = static_cast<int>(std::round(u->getQuantity() * 0.8)); // Làm tròn đúng
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
                u->setWeight(static_cast<int>(u->getWeight()*0.8));
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

void ARVN::updateScore(bool update) {}

Army::Army(Unit **unitArray, int size, string name) : name(name), LF(0), EXP(0)
{
    unitList = new UnitList(size);

    for(int i = 0; i < size; ++i){
        Unit *unit = unitArray[i];

        if(dynamic_cast<Vehicle*>(unit)){
            unitList->insert(unit);
            LF += dynamic_cast<Vehicle*>(unit)->getAttackScore();
        }else if(dynamic_cast<Infantry*>(unit)){
            unitList->insert(unit);
            EXP += dynamic_cast<Infantry*>(unit)->getAttackScore();
        }
    } 
    LF = min(LF, 1000);
    LF = max(LF, 0);

    EXP = min(EXP, 500);
    EXP = max(EXP, 0);
}

Army::~Army() {
    // TODO: Implement
    if(unitList){
        delete unitList;
        unitList = nullptr;
    }
}

void Army::fight(Army* enemy, bool defense) {
    // TODO: Implement
}

int Army::safeCeil(double value) {
    // TODO: Implement
    return static_cast<int>(ceil(value));
}

void Army::updateScore(bool update){
    // TODO: Implement
   if(update){
        LF = 0; 
        EXP = 0;
    for(Unit *unit : unitList->getUnits()){
        if(dynamic_cast<Vehicle*>(unit))
            LF += unit->getAttackScore();
        else if(dynamic_cast<Infantry*>(unit))
            EXP += unit->getAttackScore();
    }
    LF = min(LF, 1000);
    LF = max(LF, 0);

    EXP = min(EXP, 500);
    EXP = max(EXP, 0);
}
}
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
    //cout << print_UNIT_NAME(units);
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
    stringstream ss(content);
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

void Configuration::processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE) {
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

        size_t eq_pos = line.find('=');
        if (eq_pos == string::npos)
            continue;

        string key = line.substr(0, eq_pos);
        string value = line.substr(eq_pos + 1);
       
            if (key == "NUM_ROWS") {
                NUM_ROWS = stoi(value);
                hasRow = true;
                
            }

            if (key == "NUM_COLS") {
                NUM_COLS = stoi(value);
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
            
            
            if (key == "EVENT_CODE")
        {
            if (stoi(value) >= 0 && stoi(value) <= 99)
                EVENT_CODE = stoi(value);
            else
                EVENT_CODE = (stoi(value) < 0) ? 0 : (stoi(value) % 100);

        } else if(key == "ARRAY_FOREST"){
            arrayForest = parsePositions(value);
            process_pos(value,battlefield, NUM_ROWS, NUM_COLS,FOREST);
            
        }
        else if(key == "ARRAY_RIVER"){
            arrayRiver = parsePositions(value);
            process_pos(value,battlefield, NUM_ROWS, NUM_COLS,RIVER);
        }
        else if(key == "ARRAY_FORTIFICATION"){
            arrayFortification = parsePositions(value);
            process_pos(value,battlefield, NUM_ROWS, NUM_COLS, FORTIFICATION);
        }
        else if(key == "ARRAY_URBAN"){
            arrayUrban = parsePositions(value);
            process_pos(value,battlefield, NUM_ROWS, NUM_COLS,URBAN);
        }
        else if(key == "ARRAY_SPECIAL_ZONE"){
            arraySpecialZone = parsePositions(value);
            process_pos(value,battlefield, NUM_ROWS, NUM_COLS,SPECIAL_ZONE); 
        }else if(key == "UNIT_LIST"){
            string unit_list;
            size_t start_pos = value.find("[");
            size_t end_pos = value.find("]");
            if(start_pos != string::npos && end_pos == string::npos){
                unit_list += value.substr(start_pos + 1);
                while(getline(file, line)){
                    size_t close_pos = line.find("]");
                    line.erase(remove_if(line.begin(), line.end(), [](unsigned char c){ return c == '\t'; }), line.end());

                    if(close_pos != string::npos){
                        unit_list += line.substr(0, close_pos);
                        break;
                    }
                    unit_list += line;
                }
            }else if(start_pos != string::npos && end_pos != string::npos){
                value = value.substr(start_pos + 1, end_pos - start_pos - 1);
            }
            //value = removeTabs(unit_list);
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
    case FOREST: ss << "FOR"; break;
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
       // ss  << infantryTypeToString(unit.type) << "(" // sua lai
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
void Configuration::process_pos(const string &coords, TerrainType **&battlefield, int NUM_ROWS, int NUM_COLS, TerrainType const &terrain)
{
    vector<Position*> Pos;
    string clean_coords = coords;
    clean_coords.erase(remove(clean_coords.begin(), clean_coords.end(), '['), clean_coords.end());
    clean_coords.erase(remove(clean_coords.begin(), clean_coords.end(), ']'), clean_coords.end());

    stringstream ss(clean_coords);
    string token;
      
    while (getline(ss, token, ')')){ // (1,2
        if (token.empty()) continue;

        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        size_t openParen = token.find('(');
        if(openParen == string::npos) continue;

        string pos = token.substr(openParen + 1); // 1,2
        size_t comma = pos.find(',');

        string _x = pos.substr(0, comma); // 1
        string _y = pos.substr(comma + 1); // 2

            int x = stoi(_x);
            int y = stoi(_y);
        Pos.push_back(new Position(x, y));
        if(x >= 0 && y >= 0 && x < NUM_ROWS && y < NUM_COLS){
            battlefield[x][y] = terrain;
        }
    }
}

string Configuration::removeTabs(const string &input) {
    string output;
    for (char c : input) {
        if (c != ' ') { // Chỉ thêm ký tự vào output nếu không phải tab
            output += c;
        }
    }
    return output;
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
//[num_rows=10,num_cols=8,arrayForest=[(1,2),(3,5)],arrayRiver=[(0,0),(0,4)],arrayFortification=[(6,6)],arrayUrban=[(2,0)],arraySpecialZone=[(9,7)],liberationUnits=[Vehicle[vehicleType=TANK,quantity=5,weight=2,position=(1,2)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=2,position=(1,1)]],ARVNUnits=[Vehicle[vehicleType=TANK,quantity=5,weight=2,position=(3,2)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=2,position=(3,3)]],eventCode=23]

    return ss.str();
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////