#include "Unit.h"

// Unit::Unit(int quantity, int weight, Position pos)
// {
//     // TODO: implement
// }

Unit::~Unit()
{
    // TODO: implement
    quantity = 0;
    weight = 0;
    pos = Position(0, 0);
}

Position Unit::getCurrentPosition() const
{
    return pos;
}