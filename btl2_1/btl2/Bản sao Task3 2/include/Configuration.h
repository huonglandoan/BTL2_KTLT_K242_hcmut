#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "main.h"
#include "Position.h"
#include "Unit.h"
#include "Vehicle.h"
#include "Infantry.h"
#include "TerrainElement.h"
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------

class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    Unit **libUnits;
    Unit **arvnUnits;
    // Các mảng đơn vị quân được để trống (stub) trong phần hiện thực mẫu
    vector<Unit*> liberationUnits;
    vector<Unit*> ARVNUnits;
    int libsize, ARVNsize;
    vector<Position *> parsePositions(const string &input);
    bool isVehicleType(const string &type);
    bool isInfantryType(const string &type);
    int eventCode;
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
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    
    // Hint: You can add more or other methods to access the private members if needed.
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
    void process_pos(const string &coords,TerrainType **&battlefield, int NUM_ROWS, int NUM_COLS, TerrainType const &terrain);
    string removeTabs(const string &input);
    void processUnit(const string &unit_str, vector<UNIT_NAME> &units);
    int setEventCode(int code);

};

#endif