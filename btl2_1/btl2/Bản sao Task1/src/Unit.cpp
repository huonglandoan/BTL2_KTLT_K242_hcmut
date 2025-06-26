#include "Unit.h"

//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
// Unit::Unit(int quantity, int weight, Position pos)
//     : quantity(quantity), weight(weight), pos(pos)
// {}
// Unit::~Unit()
// {
//     // Virtual destructor – nếu có bộ nhớ động thì giải phóng ở đây.
   
// }
Position Unit::getCurrentPosition() const
{
    // TODO: Implement
    return this->pos;
}

void Unit::increaseQuantity(int q) {
    if (q > 0) quantity += q;
}