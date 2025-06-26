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

class Position
{
private:
    int r, c;

public:
    Position(int r, int c) : r(r), c(c) {}
    Position(const string &str_pos);

    int getRow() const { return r; }
    int getCol() const { return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }
    string str() const { return "(" + to_string(getRow()) + "," + to_string(getCol()) + ")"; }
};

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK,
    VEHICLE_UNKNOWN
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY,
    INFANTRY_UNKNOWN
};
class UnitList
{
private:
struct Node
{
    Unit *unit;
    Node *next;
    Node(Unit *unit) : unit(unit), next(nullptr) {}
};

    Node *head, *tail;
    int count;
    int capacity;
    bool isSpecial(int n) const;
    Unit *unit;
    // TODO
public:
    UnitList(int capacity) : head(nullptr), tail(nullptr), count(0), capacity(capacity) {
        capacity = (isSpecial(capacity)) ? 12 : 8;
    }
    ~UnitList();

    bool insert(Unit *unit);                   // return true if insert successfully
    bool isContain(VehicleType vehicleType);   // return true if it exists
    bool isContain(InfantryType infantryType); // return true if it exists
    string str() const;
};
class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual void fight(Army *enemy, bool defense = false) {}
    virtual string str() const {return "hi";}
};

class LiberationArmy : public Army
{

public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField) : Army(unitArray, size, name, battleField) {}
    void fight (Army *enemy, bool defense);
    string str() const;
};
class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, const Position pos) : quantity(quantity), weight(weight), pos(pos) {}
    virtual ~Unit()
    {
        quantity = 0;
        weight = 0;
        pos = Position(0, 0);
    }
    virtual bool isVehicle() const {return false;}
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const { return pos; }
    virtual string str() const;

};
class Vehicle : public Unit
{
private:
    VehicleType vehicleType;

public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType) {}
    ~Vehicle(){}
    int getAttackScore() { return static_cast<int>(vehicleType) * 304 + quantity * weight; }
    VehicleType getVehicleType() const {return vehicleType; }
    bool isVehicle() const {return true;}
    string str() const; 
};
class Infantry : public Unit
{
private:
    InfantryType infantryType;
    bool isPerfectSquare(int a) const;
    int personalNumber(int num, int year) const;

public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType) {}
    ~Infantry() {};
    int getAttackScore();
    InfantryType getInfantryType() const {return infantryType; }
    string str() const;
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
class Configuration
{
private:
    int num_rows, num_cols, eventCode;
    vector<Position *> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
    Unit **liberationUnits;
    Unit **ARVNUnits;
    int libsize, ARVNsize;
    vector<Position *> parsePositions(const string &input);
    void parseUnits(const string &input);
    VehicleType getVehicleType(const string &type)
{
    if (type == "TRUCK")
        return TRUCK;
    if (type == "MORTAR")
        return MORTAR;
    if (type == "ANTIAIRCRAFT")
        return ANTIAIRCRAFT;
    if (type == "ARMOREDCAR")
        return ARMOREDCAR;
    if (type == "APC")
        return APC;
    if (type == "ARTILLERY")
        return ARTILLERY;
    if (type == "TANK")
        return TANK;
    return VEHICLE_UNKNOWN;
}
InfantryType getInfantryType(const string &type)
{
    if (type == "SNIPER")
        return SNIPER;
    if (type == "ANTIAIRCRAFTSQUAD")
        return ANTIAIRCRAFTSQUAD;
    if (type == "MORTARSQUAD")
        return MORTARSQUAD;
    if (type == "ENGINEER")
        return ENGINEER;
    if (type == "SPECIALFORCES")
        return SPECIALFORCES;
    if (type == "REGULARINFANTRY")
        return REGULARINFANTRY;
    return INFANTRY_UNKNOWN;
}
    bool isVehicleType(const string &type) { return getVehicleType(type) != VEHICLE_UNKNOWN; }
    bool isInfantryType(const string &type) { return getInfantryType(type) != INFANTRY_UNKNOWN; }

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
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

#endif