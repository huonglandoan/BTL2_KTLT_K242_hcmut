#include "Infantry.h"

// TODO: implement
//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------

bool Infantry::isPerfectSquare(int a) const
{
    int num = (int)sqrt(a);
    return (num * num == a) ? true : false;
}
int tong(int n) {
    if(n < 10)  return n;
    return (n % 10) + tong(n/10);
}
int Infantry::personalNumber(int num, int year) const
{
    int perNum = tong(num) + tong(year);
    if(perNum < 10) return perNum;
    return personalNumber(perNum, 0);
}
int Infantry::getAttackScore() 
{
    return (modifiedScore >= 0) ? modifiedScore : attackScore;
}
string infantryTypeToString(InfantryType type){
    switch(type){
        case SNIPER: return "SNIPER";
        case ANTIAIRCRAFTSQUAD: return "ANTIAIRCRAFTSQUAD";
        case MORTARSQUAD: return "MORTARSQUAD";
        case ENGINEER: return "ENGINEER";
        case SPECIALFORCES: return "SPECIALFORCES";
        case REGULARINFANTRY: return "REGULARINFANTRY";
        default: return "UNKNOWN";
    }
}
string Infantry::str() const
{
    ostringstream oss;
    oss << "Infantry[infantryType=" << infantryTypeToString(getInfantryType()) 
        << ",quantity=" << quantity
        << ",weight=" << weight
        << ",position=" << pos.str()
        << "]";
    return oss.str();
}

