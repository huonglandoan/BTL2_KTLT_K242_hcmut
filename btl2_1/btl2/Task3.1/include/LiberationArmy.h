#ifndef _H_LIBERATIONARMY_H_
#define _H_LIBERATIONARMY_H_

#include "Army.h"
#include "ARVN.h"

class LiberationArmy : public Army {
private:
    Unit **unitArray;       // For temporary
    int size_V = 0;         // For temporary: vehicle count
    int size_I = 0;         // For temporary: infantry count
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

#endif