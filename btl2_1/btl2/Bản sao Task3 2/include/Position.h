#ifndef POSITION_H
#define POSITION_H

#include "main.h"

class Position
{
private:
    int r, c;

public:
    Position(int r, int c);
    Position() : r(0), c(0) {}
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};

#endif // POSITION_H
