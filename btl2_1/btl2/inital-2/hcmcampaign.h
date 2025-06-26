/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

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

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};
enum TerrainType
{
    ROAD,
    FOREST,
    RIVER,
    FORTIFICATION,
    URBAN,
    SPECIAL_ZONE
};

class Army {
    protected:
        int LF;        
        int EXP;       
        string name;
        UnitList *unitList;
        //BattleField *battleField;
        bool defeated = false;
        
    public:
        Army(Unit **unitArray, int size, string name);
        virtual ~Army();
        virtual void fight(Army *enemy, bool defense = false) = 0;
        virtual string str() const = 0;
        int safeCeil(double value);
        virtual void updateScore(bool update);
        int getLF() {return LF;}
        int getEXP() {return EXP;}
        UnitList* getUnitList() {return unitList;}
        //BattleField getBattleField() {return getBattleField;}
        void markAsDefeated()   {defeated = true;}
        bool isDefeated() const {return defeated;}
    };

class Position
{
private:
    int r, c;

public:
    Position(int r, int c) : r(r), c(c) {}
    Position() : r(0), c(0) {}
    Position(const string &str_pos);
    int getRow() const { return r; }
    int getCol() const { return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }
    string str() const { return "(" + to_string(getRow()) + "," + to_string(getCol()) + ")"; }
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos): quantity(quantity), weight(weight), pos(pos) {}
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    int getWeight() {return weight;}
    int getQuantity() {return quantity;}
    void setWeight(int weight);
    void setQuantity(int quantity);
};


class UnitList
{
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
    int countVehicle, countInfantry;

public:
    UnitList(int capacity);
    ~UnitList();
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    bool isSpecial(int n)   const;
    int countV() {return countVehicle;}
    int countI() {return countInfantry;}
    vector<Unit *> getUnits() const;
    string str() const;
    void remove(Unit *unit);
    vector<Unit*>getInfantryUnits() const;
    vector<Unit*>getVehicleUnits() const;

    // * Additional functions if possible
};

class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};

class BattleField
{
private:
    int n_rows, n_cols;
    // TODO
public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone);
    ~BattleField();
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *ARVN;

public:
    HCMCampaign(const string &config_file_path);
    void run();
    string printResult();
};
string infantryTypeToString(InfantryType type);
class Infantry : public Unit
{
protected:
    InfantryType infantryType;  
    bool isPerfectSquare(int a) const;
    int personalNumber(int num, int year) const;
public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType) {}
    ~Infantry() {};
    int getAttackScore() override;
    InfantryType getInfantryType() const {return infantryType; }
    string str() const override;
};
string vehicleTypeToString(VehicleType type); 
class Vehicle : public Unit
{
protected:
    VehicleType vehicleType;  
public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {}
    ~Vehicle(){}
    int getAttackScore() override;
    VehicleType getVehicleType() const {return vehicleType; }
    string str() const override;
};
class ARVN : public Army
{
    Unit **unitArray;
public:
    ARVN(Unit** unitArray, int size, string name);
    void fight(Army* enemy, bool defense=false) override;
    string str() const override;
    // * Additional functions if possible
    void updateScore(bool update) override;

};
class LiberationArmy : public Army
{
private:
    Unit **unitArray;       
    int size_V = 0;         
    int size_I = 0;         
    int nearestFibonacci(int value);
    Unit* cloneUnit(Unit* unit);
    

public:
    LiberationArmy(Unit **unitArray, int size, string name);
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    void updateScore(bool update) override{}
    int knapsackSubset(vector<Unit*>& units, int target, vector<Unit*>& result);
};



class Configuration
{
private:
    int num_rows, num_cols, eventCode;
    vector<Position *> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
    Unit **libUnits;
    Unit **arvnUnits;
    vector<Unit*> liberationUnits;
    vector<Unit*> ARVNUnits;
    int libsize, ARVNsize;
    vector<Position *> parsePositions(const string &input);
    bool isVehicleType(const string &type);
    bool isInfantryType(const string &type);
public:
struct UNIT_NAME
{
    int quantity;
    int weight;
    int position_x;
    int position_y;
    bool armyBelong;
    InfantryType itype;
    VehicleType vtype;
};

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
    void processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE);
    string print_battlefield(const TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS);
    string print_UNIT_NAME(const vector<UNIT_NAME> &units);
    void clearBattlefield(TerrainType **&battlefield, const int &NUM_ROWS, const int &NUM_COLS);
    void process_pos(const string &coords,TerrainType **&battlefield, int NUM_ROWS, int NUM_COLS, TerrainType const &terrain);
    string removeTabs(const string &input);
    void processUnit(const string &unit_str, vector<UNIT_NAME> &units);


};
#endif