#ifndef _H_ARVN_H_
#define _H_ARVN_H_

#include "Army.h"
#include "LiberationArmy.h"

class ARVN : public  Army
{
    // TODO: implement
    Unit **unitArray;
    int size_V = 0;
    int size_I = 0;
public:
    ARVN(Unit** unitArray, int size, string name): Army(unitArray,size,name) {
    
        this->unitArray = new Unit*[size];
        size_V = 0;
        size_I = 0;
    
        for (int i = 0; i < size; ++i) {
            this->unitArray[i] = cloneUnit(unitArray[i]);  // Chỉ clone thôi
            if (dynamic_cast<Vehicle*>(unitArray[i])) size_V++;
            else if (dynamic_cast<Infantry*>(unitArray[i])) size_I++;
        }
       //cout << "ARVNArmy constructor called\n";  
    }
    void fight(Army* enemy, bool defense=false) override;
    string str() const override;
    // * Additional functions if possible

};

#endif