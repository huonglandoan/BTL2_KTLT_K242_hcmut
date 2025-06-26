#ifndef UNIT_H
#define UNIT_H

#include "Position.h"

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
    virtual int safeCeil(double value) {
        double  diff = abs(value - round(value));  
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
};

#endif // UNIT_H
