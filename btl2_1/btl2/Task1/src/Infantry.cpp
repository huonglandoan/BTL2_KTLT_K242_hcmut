#include "Infantry.h"

// TODO: implement
Infantry::Infantry(int quantity, int weight, const Position pos, InfantryType infantryType):Unit(quantity, weight, pos), infantryType(infantryType){
    adjQuantity();
}

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
    int originalQuantity = quantity;
    int score = (infantryType * 56) + (originalQuantity * weight);
    if (infantryType == SPECIALFORCES && isPerfectSquare(weight)) {
        score += 75;
    }
    return score;
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
void Infantry::adjQuantity(){
   
    int score = static_cast<int>(infantryType) * 56 + quantity * weight;
    
    if (infantryType == SPECIALFORCES && isPerfectSquare(weight))
        score += 75;

    int perNum = personalNumber(score, 1975);

    if (perNum > 7){
        this->quantity = quantity + safeCeil(quantity * 0.2);
    }else if (perNum < 3 && quantity > 1){
        this->quantity = quantity - safeCeil(quantity * 0.1);
    } else {
        this->quantity = quantity;
        }
}