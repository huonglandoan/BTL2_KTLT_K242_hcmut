#ifndef _H_ARMY_H_
#define _H_ARMY_H_
#include "UnitList.h"
#include "BattleField.h"
using namespace std;

class BattleField;

class Army {
protected:
    int LF;        // * Tổng điểm từ các phương tiện (Vehicle)
    int EXP;       // * Tổng điểm từ các lực lượng bộ binh (Infantry)
    string name;
    UnitList *unitList;
    BattleField *battleField;
    bool defeated = false;
    
public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    Unit* cloneUnit(Unit* unit);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    virtual int safeCeil(double value) { double diff = abs(value - round(value));  
        return (diff < 1e-9) ? round(value) : ceil(value);}
    virtual void updateScore(bool update);
    virtual int getLF() const {return LF;}
    virtual int getEXP() const {return EXP;}
    UnitList* getUnitList() {return unitList;}
    //BattleField getBattleField() {return getBattleField;}
    // * Additional functions if possible
    void setLF(int n) {this->LF = n;}
    void setEXP(int n) {this->EXP = n;}
    void markAsDefeated()   {defeated = true;}
    bool isDefeated() const {return defeated;}
    virtual void checkRange(int& num, int MAX) const {
        num = std::max(0, std::min(num, MAX));
    }

    virtual bool isARVNArmy() const = 0;
    virtual bool isLiberationArmy() const = 0;
};

#endif
