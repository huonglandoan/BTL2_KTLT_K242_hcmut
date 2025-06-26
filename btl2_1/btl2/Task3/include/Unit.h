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
    virtual ~Unit() = default;
    virtual int getAttackScore() = 0;
    //int getAttackScoreinFight();
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    virtual Unit* clone() const = 0;
    int getQuantity() const { return this->quantity; }
    int getWeight() const { return this->weight; }
    virtual void setWeight(int w) { this->weight = w; }
    virtual void setQuantity(int q) {this->quantity = q;}
    void increaseQuantity(int q);  
    virtual int safeCeil(double value) const { double diff = abs(value - round(value));  
        return (diff < 1e-9) ? round(value) : ceil(value);}
};

#endif // UNIT_H
