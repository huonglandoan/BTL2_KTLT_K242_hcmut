#ifndef INFANTRY_H
#define INFANTRY_H

#include "Unit.h"

enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};
string infantryTypeToString(InfantryType type);
class Infantry : public Unit
{
    private:
    InfantryType infantryType;
    bool isPerfectSquare(int a) const;
    int personalNumber(int num, int year) const;

public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType);
    int getAttackScore();
    InfantryType getInfantryType() const {return infantryType; }
    string str() const;
    void adjQuantity();
};

#endif // INFANTRY_H