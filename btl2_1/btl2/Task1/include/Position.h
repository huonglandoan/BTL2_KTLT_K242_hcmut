#ifndef POSITION_H
#define POSITION_H

#include "main.h"

class Position
{
private:
    int r, c;

public:
    Position(int r, int c) : r(r), c(c) {}
    Position() : r(0), c(0) {}
    Position(const string &str_pos);
    int getRow() const { return r; }
    int getCol() const { return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }
    string str() const { return "(" + to_string(getRow()) + "," + to_string(getCol()) + ")"; }
};

#endif // POSITION_H
