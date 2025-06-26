#include "Position.h"

// Position::Position(int r, int c) : r(r), c(c)
// {
//     // TODO: implement
// }

Position::Position(const string &str_pos)
{
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;

}

// int Position::getRow() const { return r; }

// int Position::getCol() const { return c; }

// void Position::setRow(int r)
// { // TODO: implement
// }

// void Position::setCol(int c)
// {
//     // TODO: implement
// }

// string Position::str() const
// {
//     // TODO: implement
//     return "";
// }