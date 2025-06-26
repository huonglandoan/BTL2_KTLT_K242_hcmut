#include "main.h"

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
struct UNIT_NAME
{
    int quantity;
    int weight;
    int position_x;
    int position_y;
    bool armyBelong;
    InfantryType type;
};
inline string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
void processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE);
string print_battlefield(const TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS);
string print_UNIT_NAME(const vector<UNIT_NAME> &units);
void clearBattlefield(TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS);
