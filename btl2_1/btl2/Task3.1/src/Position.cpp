#include "Position.h"

//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
Position::Position(int r, int c) : r(r), c(c){}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { 
   this->r = r;
}
void Position::setCol(int c) { 
    this->c = c;
}
string Position::str() const {
    stringstream ss;
    ss << "(" << r << "," << c << ")";
    return ss.str();
}
Position::Position(const string &str_pos) {
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;
}