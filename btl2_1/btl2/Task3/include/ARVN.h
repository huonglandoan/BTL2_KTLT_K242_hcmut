#ifndef _H_ARVN_H_
#define _H_ARVN_H_

#include "Army.h"

class ARVN : public Army
{
    // TODO: implement
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

#endif