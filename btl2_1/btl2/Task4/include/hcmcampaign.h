// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType {
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType {
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

//!-----------------------------------------------------
//! CLASS Position
//!-----------------------------------------------------
class Position {
private:
    int r, c;
public:
    Position(int r, int c);
    Position() : r(0), c(0) {}
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};

//!-----------------------------------------------------
//! CLASS Unit
//!-----------------------------------------------------
class Unit {
protected:
    int quantity, weight;
    Position pos;
public:
    Unit(int quantity, int weight, Position pos): quantity(quantity), weight(weight), pos(pos) {}
    virtual ~Unit() = default;
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    virtual Unit* clone() const = 0;
    int getQuantity() const { return quantity; }
    int getWeight() const { return weight; }
    virtual void setWeight(int w) { weight = w; }
    virtual void setQuantity(int q) {quantity = q;}
    void increaseQuantity(int q);  
    virtual int safeCeil(double value) const { 
        double diff = abs(value - round(value));  
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
};


//!-----------------------------------------------------
//! CLASS Infantry : public Unit
//!-----------------------------------------------------
class Infantry : public Unit {
protected:
    InfantryType infantryType;  
    bool isPerfectSquare(int a) const;
    int personalNumber(int num, int year) const;
    int attackScore = -1;
    int modifiedScore = -1;
    void init() {
        int tmpScore = static_cast<int>(infantryType) * 56 + quantity * weight;
        if (infantryType == SPECIALFORCES && isPerfectSquare(weight)) {
            tmpScore += 75;
        }
        int perNum = personalNumber(tmpScore, 1975);
        int q = quantity;

        if (perNum > 7) {
            q = safeCeil(quantity + quantity * 0.2);
        } else if (perNum < 3 && quantity > 1) {
            q = safeCeil(quantity - quantity * 0.1);
        }
       
        Unit::setQuantity(q);
        attackScore = calcScore(); 
    }
    int calcScore() const {
        int score = static_cast<int>(infantryType) * 56 + quantity * weight;
        return safeCeil(score);
    }
public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType) {init();}
    int getAttackScore() override;
    InfantryType getInfantryType() const {return infantryType; }
    string str() const override;
    Unit *clone() const override{
        return new Infantry(getQuantity(), getWeight(), getCurrentPosition(), getInfantryType());
    }
    void setWeight(int w) override{
        Unit::setWeight(w);
        attackScore = calcScore();
    }
    void setQuantity(int q) override{
        Unit::setQuantity(q);
        attackScore = calcScore();
    }
    void setAttackScore(int score) {
        modifiedScore = score;
    }
    void resetAttackScore() {
        modifiedScore = -1;
    }
};
//!-----------------------------------------------------
//! CLASS Vehicle : public Unit
//!-----------------------------------------------------
class Vehicle : public Unit {
protected:
    VehicleType vehicleType;  
    int attackScore = -1;
    int modifiedScore = -1;
public:    
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {
        attackScore = (static_cast<int>(vehicleType) * 304 + quantity * weight) / 30.0;
        //cout << "new Veh\n";
    }
    int getAttackScore() override;
    VehicleType getVehicleType() const {return vehicleType; }
    string str() const override;
    void setWeight(int w) override{
        Unit::setWeight(w);
    }
    void setQuantity(int q) override{
        Unit::setQuantity(q);
    }
    Unit *clone() const override{
        return new Vehicle(getQuantity(), getWeight(), getCurrentPosition(), getVehicleType());
    }
    void setAttackScore(int score){
        modifiedScore = score;
    }
    void resetAttackScore(){
        modifiedScore = -1;
    }
};

//!-----------------------------------------------------
//! CLASS UnitList
//!-----------------------------------------------------
class UnitList {
private:
struct Node{
    Unit *unit;
    Node *next;
    Node *prev;
    Node(Unit *unit): unit(unit), next(nullptr) {}
};
    Node *head, *tail;
    int count; 
    int capacity;
   // bool mergeMode = true;
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
    void addUnit(Unit *u, bool &isInserted);
    void CheckAndRemove();
    void insertToTail(Unit* unit);
    void removeNode(Node* node);
};

//!-----------------------------------------------------
//! CLASS Army 
//!-----------------------------------------------------
class Army {
protected:
    int LF;        
    int EXP;       
    string name;
    UnitList *unitList;
    BattleField *battleField;
    bool defeated = false;
public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    Unit* cloneUnit(Unit* unit);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    virtual int safeCeil(double value) { double diff = abs(value - round(value));  
        return (diff < 1e-9) ? round(value) : ceil(value);}
    virtual void updateScore(bool update);
    virtual int getLF() const {return LF;}
    virtual int getEXP() const {return EXP;}
    UnitList* getUnitList() {return unitList;}
    //BattleField getBattleField() {return getBattleField;}
    void setLF(int n) {this->LF = n;}
    void setEXP(int n) {this->EXP = n;}
    void markAsDefeated()   {defeated = true;}
    bool isDefeated() const {return defeated;}
    virtual void checkRange(int& num, int MAX) const {
        num = std::max(0, std::min(num, MAX));
    }
    virtual bool isARVNArmy() const = 0;
    virtual bool isLiberationArmy() const = 0;
};

//!-----------------------------------------------------
//! CLASS LiberationArmy
//!-----------------------------------------------------
class LiberationArmy : public Army {
private:
    Unit **unitArray;       
    int size_V = 0;         
    int size_I = 0;         
    int nearestFibonacci(int value);    
    UnitList* temp;
public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField);
    ~LiberationArmy();
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    int minSubsetSumGreaterThan(const vector<Unit*>& units, int target);
    void copyEnemyList(UnitList *enemyUnitList);
    vector<Unit*> selectMinSubset(const std::vector<Unit*>& units, int target);
    bool isLiberationArmy() const override { return true; }
    bool isARVNArmy() const override { return false; }
};

//!-----------------------------------------------------
//! CLASS ARVN
//!-----------------------------------------------------
class ARVN : public Army {
    Unit **unitArray;
    int size_V = 0;
    int size_I = 0;
public:
    ARVN(Unit** unitArray, int size, string name, BattleField *battleField);
    void fight(Army* enemy, bool defense=false) override;
    string str() const override;
    bool isARVNArmy() const override { return true; }
    bool isLiberationArmy() const override { return false; }
};


//!-----------------------------------------------------
//! CLASS TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------
enum TerrainType {
    ROAD,
    MOUNTAIN,
    RIVER,
    FORTIFICATION,
    URBAN,
    SPECIAL_ZONE
};
class TerrainElement {
protected:
    Position pos; 
    TerrainType terrain;
    double calculateDistance(const Position& pos1, const Position& pos2) {
        int rowDiff = pos1.getRow() - pos2.getRow();
        int colDiff = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
    }
    int safeCeil(double value) {
        double diff = abs(value - round(value));
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
    int safeFloor(double value) {
        int base = (int)value;
        double frac = value - base;
        if (frac < 0.5 - 1e-6)
        return base;
    else
        return base + 1;    }
public:
    TerrainElement(Position pos, TerrainType terrainType = ROAD);
    virtual ~TerrainElement();
    virtual void getEffect(Army *army){}
    TerrainType getTerrain() {return terrain; }
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos, ROAD) {}
    void getEffect(Army *army) override;
};

class Mountain : public TerrainElement {
    public:
    Mountain(Position pos) : TerrainElement(pos, MOUNTAIN ) {}
    void getEffect(Army *army) override;        
};

class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos, RIVER) {}
    void getEffect(Army *army) override;
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos, URBAN) {}
    void getEffect(Army *army) override;
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos, FORTIFICATION) {}
    void getEffect(Army *army) override;
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos, SPECIAL_ZONE) {}
    void getEffect(Army *army) override;
};

//!-----------------------------------------------------
//! CLASS BattleField
//!-----------------------------------------------------
class BattleField {
private:
    int n_rows, n_cols;
    TerrainElement ***terrain;
public:
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    ~BattleField();
    TerrainElement* getElement(int r, int c) const;
    string str() const;
};

//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
static string vehicleTypeToString(VehicleType vt) {
    switch(vt) {
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
static string infantryTypeToString(InfantryType it) {
    switch(it) {
        case SNIPER:              return "SNIPER";
        case ANTIAIRCRAFTSQUAD:     return "ANTIAIRCRAFTSQUAD";
        case MORTARSQUAD:           return "MORTARSQUAD";
        case ENGINEER:              return "ENGINEER";
        case SPECIALFORCES:         return "SPECIALFORCES";
        case REGULARINFANTRY:       return "REGULARINFANTRY";
        default:                    return "UNKNOWN";
    }
}
inline string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    vector<Unit*> liberationUnits;
    vector<Unit*> ARVNUnits;
    Unit **libUnits;
    Unit **arvnUnits;
    bool isVehicleType(const string &type);
    bool isInfantryType(const string &type);
    int libsize, ARVNsize;
    int eventCode;
    vector<Position *> parsePositions(const string &input);
public:
    struct UNIT_NAME {
        int quantity;
        int weight;
        int position_x;
        int position_y;
        bool armyBelong;
        InfantryType itype;
        VehicleType vtype;
    };
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    vector<Unit*>& getLiberationUnits() { return liberationUnits; }
    vector<Unit*>& getARVNUnits() { return ARVNUnits; }
    void processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE);
    string print_battlefield(const TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS);
    string print_UNIT_NAME(const vector<UNIT_NAME> &units);
    void clearBattlefield(TerrainType **&battlefield, const int &NUM_ROWS, const int &NUM_COLS);
    void processUnit(const string &unit_str, vector<UNIT_NAME> &units);
    int setEventCode(int code);
};

//!-----------------------------------------------------
//! Lớp HCMCampaign
//!-----------------------------------------------------
class HCMCampaign {
private:
    Configuration*
    config;
    BattleField* battleField;
    LiberationArmy* liberationArmy;
    ARVN* arvnArmy;
public:
    HCMCampaign(const string & config_file_path);
    ~HCMCampaign();
    void run();
    string printResult();
    void remove(Army *army);
};
#endif