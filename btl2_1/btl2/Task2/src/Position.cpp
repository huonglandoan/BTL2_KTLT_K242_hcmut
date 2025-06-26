#include "Position.h"

//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------

Position::Position(const string &str_pos)
{
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;
}