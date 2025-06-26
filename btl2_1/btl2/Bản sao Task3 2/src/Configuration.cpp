#include "Configuration.h"

// * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
static string vehicleTypeToString(VehicleType vt) {
    switch(vt)
    {
        case TRUCK:         return "TRUCK";
        case MORTAR:        return "MORTAR";
        case ANTIAIRCRAFT:  return "ANTIAIRCRAFT";
        case ARMOREDCAR:    return "ARMOREDCAR";
        case APC:           return "APC";
        case ARTILLERY:     return "ARTILLERY";
        case TANK:          return "TANK";
        default:            return "UNKNOWN";
    }
}
static string infantryTypeToString(InfantryType it)
    {
        switch(it)
        {
            case SNIPER:              return "SNIPER";
            case ANTIAIRCRAFTSQUAD:     return "ANTIAIRCRAFTSQUAD";
            case MORTARSQUAD:           return "MORTARSQUAD";
            case ENGINEER:              return "ENGINEER";
            case SPECIALFORCES:         return "SPECIALFORCES";
            case REGULARINFANTRY:       return "REGULARINFANTRY";
            default:                    return "UNKNOWN";
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
    // TODO
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
                    line.erase(remove_if(line.begin(), line.end(), [](unsigned char c){ return c == '\t'; }), line.end());

                    if(close_pos != string::npos){
                        unit_list += line.substr(0, close_pos);
                        break;
                    }
                    unit_list += line;
                }
                 value = unit_list;
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

    stringstream ss(clean_coords);
    string token;
      
    while (getline(ss, token, ')')){ // (1,2
        if (token.empty()) continue;
       
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        size_t openParen = token.find('('); 
        if(openParen == string::npos) continue;

        string pos = token.substr(openParen + 1); // 1,2
        size_t comma = pos.find(',');
        //cout << pos << endl;
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
//[num_rows=10,num_cols=8,arrayForest=[(1,2),(3,5)],arrayRiver=[(0,0),(0,4)],arrayFortification=[(6,6)],arrayUrban=[(2,0)],arraySpecialZone=[(9,7)],liberationUnits=[Vehicle[vehicleType=TANK,quantity=5,weight=2,position=(1,2)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=2,position=(1,1)]],ARVNUnits=[Vehicle[vehicleType=TANK,quantity=5,weight=2,position=(3,2)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=2,position=(3,3)]],eventCode=23]

    return ss.str();
}
int Configuration::setEventCode(int code){
    if(code >= 100){
        return code % 100;
    }else if(code < 0){
        return 0;
    }else {return code;}
}