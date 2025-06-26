#include "../unit_test_Task2.hpp"

bool UNIT_TEST_Task2::Task251()
{
    string name = "Task221";
    //! data ------------------------------------
    Vehicle tankOfLiber(20, 20, Position(1, 2), MORTAR);
    Vehicle truckOfLiber(15, 10, Position(2, 2), TRUCK);
    Infantry sniperOfLiber(10, 20, Position(1, 1), SNIPER);

    Vehicle tankOfAr(5, 20, Position(3, 2), MORTAR);
    Vehicle truckOfAr(1, 10, Position(3, 1), TRUCK);
    Infantry sniperOfAr(7, 20, Position(3, 3), SNIPER);

    Unit** unitArrayOfLiber = new Unit*[3];
    unitArrayOfLiber[0] = &tankOfLiber;
    unitArrayOfLiber[1] = &truckOfLiber;
    unitArrayOfLiber[2] = &sniperOfLiber;

    Unit** unitArrayOfAr = new Unit*[3];
    unitArrayOfAr[0] = &tankOfAr;
    unitArrayOfAr[1] = &truckOfAr;
    unitArrayOfAr[2] = &sniperOfAr;

    LiberationArmy* liberationArmy = new LiberationArmy(unitArrayOfLiber, 3, "LiberationArmy");
    ARVN* arvn = new ARVN(unitArrayOfAr, 3, "ARVN"); 
    stringstream output;
    output << liberationArmy->str() << endl;
    output << arvn->str() << endl;   
    
    //! process ---------------------------------
    Army* enemyLiber = arvn;
    liberationArmy->fight(enemyLiber, false);
    Army* enemyAr = liberationArmy;
    arvn->fight(enemyAr, false);
    
    //! expect ----------------------------------
    string expect = "LiberationArmy[LF=29,EXP=200,unitList=UnitList[count_vehicle=2;count_infantry=1;Infantry[infantryType=SNIPER,quantity=10,weight=20,position=(1,1)],Vehicle[vehicleType=MORTAR,quantity=20,weight=20,position=(1,2)],Vehicle[vehicleType=TRUCK,quantity=15,weight=10,position=(2,2)]]]\n"
                    "ARVN[LF=15,EXP=180,unitList=UnitList[count_vehicle=2;count_infantry=1;Infantry[infantryType=SNIPER,quantity=9,weight=20,position=(3,3)],Vehicle[vehicleType=MORTAR,quantity=5,weight=20,position=(3,2)],Vehicle[vehicleType=TRUCK,quantity=1,weight=10,position=(3,1)]]]\n"
                    "* After the fight\n"
                    "LiberationArmy[LF=20,EXP=180,unitList=UnitList[count_vehicle=2;count_infantry=1;"
                    "Infantry[infantryType=SNIPER,quantity=9,weight=20,position=(3,3)],"
                    "Vehicle[vehicleType=TRUCK,quantity=16,weight=10,position=(2,2)],"
                    "Vehicle[vehicleType=MORTAR,quantity=5,weight=20,position=(3,2)]]]\n"
                    "ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]\n"; // True (1) if all 12 insertions succeeded and 13th failed\n"
    
    //! output ----------------------------------
    output << "* After the fight" << endl;
    output << liberationArmy->str() << endl;
    output << arvn->str() << endl;
    
    //! remove data -----------------------------
    delete liberationArmy;
    delete arvn;
    delete[] unitArrayOfLiber;
    delete[] unitArrayOfAr;
    
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Task2::Task252()
{
    string name = "Task222";
    //! data ------------------------------------
    Vehicle tankOfLiber1(20, 20, Position(1, 2), MORTAR);
    Vehicle tankOfLiber2(5, 20, Position(3, 2), MORTAR);
    Infantry sniperOfLiber1(10, 20, Position(1, 0), SNIPER);
    Infantry sniperOfLiber2(10, 20, Position(1, 1), SNIPER);
    Unit** unitArrayOfLiber8 = new Unit*[4];
    unitArrayOfLiber8[0] = &tankOfLiber1;
    unitArrayOfLiber8[1] = &tankOfLiber2;
    unitArrayOfLiber8[2] = &sniperOfLiber1;
    unitArrayOfLiber8[3] = &sniperOfLiber2;
    LiberationArmy* liberationArmy8 = new LiberationArmy(unitArrayOfLiber8, 4, "LiberationArmy");
    
    //! process ---------------------------------
    
    //! expect ----------------------------------
    string expect = "LiberationArmy[LF=38,EXP=400,unitList=UnitList[count_vehicle=1;count_infantry=1;Infantry[infantryType=SNIPER,quantity=20,weight=20,position=(1,0)],Vehicle[vehicleType=MORTAR,quantity=25,weight=20,position=(1,2)]]]\n"; // True (1) if all 12 insertions succeeded and 13th failed\n"
    
    //! output ----------------------------------
    stringstream output;
    output << liberationArmy8->str() << endl;
    
    //! remove data -----------------------------
    delete liberationArmy8;
    
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
// bool UNIT_TEST_Task2::Task253()
// {
//     string name = "Task223";
//     stringstream output;
//     //! data ------------------------------------
//     Infantry* sniper = new Infantry(10, 5, Position(3, 5), SNIPER); // Adjacent to element
//     Infantry* antiarcraftsquad = new Infantry(8, 6, Position(3, 7), ANTIAIRCRAFTSQUAD); // Adjacent to element
//     Vehicle* truck = new Vehicle(10, 5, Position(4, 4), TRUCK); // Adjacent to element
//     Vehicle* mortar = new Vehicle(8, 6, Position(6, 4), MORTAR); // Adjacent to element
//     Unit* unitArray[4] = {sniper, antiarcraftsquad, truck, mortar};
//     Army* arvn = new ARVN(unitArray, 4, "TestArmy");

//     Infantry* engineer = new Infantry(5, 8, Position(0, 2), ENGINEER); // Within radius 2
//     Infantry* specialforces = new Infantry(4, 9, Position(0, 3), SPECIALFORCES); // Within radius 2
//     Infantry* regularinfantry = new Infantry(3, 10, Position(0, 3), REGULARINFANTRY); // Within radius 2
//     Vehicle* apc = new Vehicle(4, 9, Position(0, 3), APC); // Within radius 2
//     Vehicle* artillery = new Vehicle(3, 10, Position(0, 3), ARTILLERY);
//     Vehicle* tank = new Vehicle(2, 11, Position(0, 4), TANK);
//     Unit* unitArray2[6] = {engineer, specialforces, apc, regularinfantry, artillery, tank};
//     Army* liber = new LiberationArmy(unitArray2, 6, "TestArmy");
    
//     //! process ---------------------------------
//     output << "Initial Army: " << endl;
//     output << "1. " << liber->str() << endl;
//     output << "2. " << arvn->str() << endl;

//     output << "Liberation attack ARVN: " << endl;
//     liber->fight(arvn, false);
//     output << "After Attack: " << endl;
//     output << "1. " << liber->str() << endl;
//     output << "2. " << arvn->str() << endl;

//     output << "ARVN defends Liberation: " << endl;
//     arvn->fight(liber, true);
//     output << "After defends: " << endl;
//     output << "1. " << liber->str() << endl;
//     output << "2. " << arvn->str() << endl;
//     //! expect ----------------------------------
//     string expect = "Initial Army: \n"
//     "1. LiberationArmy[LF=156,EXP=500,unitList=UnitList[count_vehicle=3;count_infantry=3;"
//     "Infantry[infantryType=REGULARINFANTRY,quantity=4,weight=10,position=(0,3)],"
//     "Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],"
//     "Infantry[infantryType=ENGINEER,quantity=5,weight=8,position=(0,2)],"
//     "Vehicle[vehicleType=APC,quantity=4,weight=9,position=(0,3)],"
//     "Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],"
//     "Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)]]]\n"
//     "2. ARVN[LF=14,EXP=176,unitList=UnitList[count_vehicle=2;count_infantry=2;"
//     "Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],"
//     "Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(3,5)],"
//     "Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)],"
//     "Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)]]]\n"
//     "Liberation attack ARVN: \n"
//     "After Attack: \n"
//     "1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]]]\n"
//     "2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]\n"
//     "ARVN defends Liberation: \n"
//     "After defends: \n"
//     "1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]]]\n"
//     "2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]\n";
//     //! output ----------------------------------
  
    
//     //! remove data -----------------------------
//     delete sniper;
//     delete antiarcraftsquad;
//     delete truck;
//     delete mortar;
//     delete engineer;
//     delete specialforces;
//     delete regularinfantry;
//     delete apc;
//     delete artillery;
//     delete tank;
//     //! result ----------------------------------
//     return printResult(output.str(), expect, name);
// }
// bool UNIT_TEST_Task2::Task252()
// {
//     string name = "Task222";
//     //! data ------------------------------------
//     Vehicle tankOfLiber1(20, 20, Position(1, 2), MORTAR);
//     Vehicle tankOfLiber2(5, 20, Position(3, 2), MORTAR);
//     Infantry sniperOfLiber1(10, 20, Position(1, 0), SNIPER);
//     Infantry sniperOfLiber2(10, 20, Position(1, 1), SNIPER);
//     Unit** unitArrayOfLiber8 = new Unit*[4];
//     unitArrayOfLiber8[0] = &tankOfLiber1;
//     unitArrayOfLiber8[1] = &tankOfLiber2;
//     unitArrayOfLiber8[2] = &sniperOfLiber1;
//     unitArrayOfLiber8[3] = &sniperOfLiber2;
//     LiberationArmy* liberationArmy8 = new LiberationArmy(unitArrayOfLiber8, 4, "LiberationArmy");
    
//     //! process ---------------------------------
    
//     //! expect ----------------------------------
//     string expect = "LiberationArmy[LF=38,EXP=400,unitList=UnitList[count_vehicle=1;count_infantry=1;Infantry[infantryType=SNIPER,quantity=20,weight=20,position=(1,0)],Vehicle[vehicleType=MORTAR,quantity=25,weight=20,position=(1,2)]]]\n"; // True (1) if all 12 insertions succeeded and 13th failed\n"
    
//     //! output ----------------------------------
//     stringstream output;
//     output << liberationArmy8->str() << endl;
    
//     //! remove data -----------------------------
//     delete liberationArmy8;
    
//     //! result ----------------------------------
//     return printResult(output.str(), expect, name);
// }
bool UNIT_TEST_Task2::Task253()
{
    string name = "Task223";
    stringstream output;
    //! data ------------------------------------
    Infantry* sniper = new Infantry(10, 5, Position(3, 5), SNIPER); // Adjacent to element
    Infantry* antiarcraftsquad = new Infantry(8, 6, Position(3, 7), ANTIAIRCRAFTSQUAD); // Adjacent to element
    Vehicle* truck = new Vehicle(10, 5, Position(4, 4), TRUCK); // Adjacent to element
    Vehicle* mortar = new Vehicle(8, 6, Position(6, 4), MORTAR); // Adjacent to element
    Unit* unitArray[4] = {sniper, antiarcraftsquad, truck, mortar};
    Army* arvn = new ARVN(unitArray, 4, "TestArmy");

    Infantry* engineer = new Infantry(5, 8, Position(0, 2), ENGINEER); // Within radius 2
    Infantry* specialforces = new Infantry(4, 9, Position(0, 3), SPECIALFORCES); // Within radius 2
    Infantry* regularinfantry = new Infantry(3, 10, Position(0, 3), REGULARINFANTRY); // Within radius 2
    Vehicle* apc = new Vehicle(4, 9, Position(0, 3), APC); // Within radius 2
    Vehicle* artillery = new Vehicle(3, 10, Position(0, 3), ARTILLERY);
    Vehicle* tank = new Vehicle(2, 11, Position(0, 4), TANK);
    Unit* unitArray2[6] = {engineer, specialforces, apc, regularinfantry, artillery, tank};
    Army* liber = new LiberationArmy(unitArray2, 6, "TestArmy");
    
    //! process ---------------------------------
    output << "Initial Army: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "Liberation attack ARVN: " << endl;
    liber->fight(arvn, false);
    output << "After Attack: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN defends Liberation: " << endl;
    arvn->fight(liber, true);
    output << "After defends: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;
    //! expect ----------------------------------
    string expect = "Initial Army: \n"
    "1. LiberationArmy[LF=156,EXP=500,unitList=UnitList[count_vehicle=3;count_infantry=3;"
    "Infantry[infantryType=REGULARINFANTRY,quantity=4,weight=10,position=(0,3)],"
    "Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],"
    "Infantry[infantryType=ENGINEER,quantity=5,weight=8,position=(0,2)],"
    "Vehicle[vehicleType=APC,quantity=4,weight=9,position=(0,3)],"
    "Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],"
    "Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)]]]\n"
    "2. ARVN[LF=14,EXP=176,unitList=UnitList[count_vehicle=2;count_infantry=2;"
    "Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],"
    "Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(3,5)],"
    "Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)],"
    "Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)]]]\n"
    "Liberation attack ARVN: \n"
    "After Attack: \n"
    "1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]]]\n"
    "2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]\n"
    "ARVN defends Liberation: \n"
    "After defends: \n"
    "1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]]]\n"
    "2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]\n";
    //! output ----------------------------------
  
    
    //! remove data -----------------------------
    delete sniper;
    delete antiarcraftsquad;
    delete truck;
    delete mortar;
    delete engineer;
    delete specialforces;
    delete regularinfantry;
    delete apc;
    delete artillery;
    delete tank;
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
bool UNIT_TEST_Task2::Task254()
{
    string name = "Task224";
    stringstream output;
    //! data ------------------------------------
    Infantry* libInf1 = new Infantry(12, 6, Position(0, 0), SNIPER);
    Infantry* libInf2 = new Infantry(11, 5, Position(0, 2), REGULARINFANTRY);
    Vehicle* libVeh1 = new Vehicle(10, 5, Position(1, 1), TRUCK);
    Unit* unitsLib[3] = { libInf1, libInf2, libVeh1 };
    Army* liber = new LiberationArmy(unitsLib, 3, "LibArmy");
    liber->setEXP(500);
    liber->setLF(2);

    Infantry* arvnInf1 = new Infantry(9, 6, Position(3, 2), SPECIALFORCES);
    Infantry* arvnInf2 = new Infantry(10, 7, Position(2, 3), ANTIAIRCRAFTSQUAD);
    Vehicle* arvnVeh1 = new Vehicle(11, 4, Position(4, 4), MORTAR);
    Unit* unitsArvn[3] = { arvnInf1, arvnInf2, arvnVeh1 };
    Army* arvn = new ARVN(unitsArvn, 3, "ARVN");
    arvn->setEXP(500);
    arvn->setLF(12);
    //! process ---------------------------------
    output << "Liberation attacks ARVN:" << endl;
    liber->fight(arvn, false);
    output << "After Attack:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN defends Liberation:" << endl;
    arvn->fight(liber, true);
    output << "After Defense:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    //! expect ----------------------------------
    string expect = "Liberation attacks ARVN:\nAfter Attack:\n1. LiberationArmy[LF=12,EXP=476,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]]]]\n2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]]\nARVN defends Liberation:\nAfter Defense:\n1. LiberationArmy[LF=12,EXP=476,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]]]]\n2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0]]]";
    //! output ----------------------------------
    
    //! remove data -----------------------------
    delete libInf1;
    delete libInf2;
    delete libVeh1;
    delete arvnInf1;
    delete arvnInf2;
    delete arvnVeh1;
    delete liber;
    delete arvn;    
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
bool UNIT_TEST_Task2::Task255()
{
    string name = "Task225";
    stringstream output;
    //! data ------------------------------------
    Infantry* sniper = new Infantry(12, 5, Position(4, 4), SNIPER);
    Infantry* regular1 = new Infantry(14, 5, Position(1, 4), REGULARINFANTRY);
    Infantry* special = new Infantry(15, 6, Position(0, 1), SPECIALFORCES);
    Vehicle* truck1 = new Vehicle(12, 5, Position(2, 2), TRUCK);

    Unit* unitArray[] = {sniper, regular1, special, truck1};
    Army *liber = new LiberationArmy(unitArray, 4, "LiberationArmy"); // bỏ qua battlefield

    Infantry* aa = new Infantry(12, 6, Position(4, 0), ANTIAIRCRAFTSQUAD);
    Infantry* regular = new Infantry(13, 5, Position(0, 5), REGULARINFANTRY);
    Vehicle* mortar = new Vehicle(14, 4, Position(3, 0), MORTAR);
    Vehicle* truck = new Vehicle(11, 5, Position(2, 3), TRUCK);

    Unit* unitArray2[] = {aa, regular, mortar, truck};
    Army *arvn =  new ARVN(unitArray2, 4, "ARVN"); // bỏ qua battlefield artillery, tank};
    
    //! process ---------------------------------
    output << "Liberation attacks ARVN (Round 2):" << endl;
    liber->fight(arvn, false);
    output << "After Liberation Attack:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN defends Liberation (Round 2):" << endl;
    arvn->fight(liber, true);
    output << "After ARVN Defense:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;
    //! expect ----------------------------------
    std::string expect = "Liberation attacks ARVN (Round 2):\n\
    After Liberation Attack:\n\
    1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n\
    2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n\
    ARVN defends Liberation (Round 2):\n\
    After ARVN Defense:\n\
    1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n\
    2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]";
        //! output ----------------------------------
  
    
    //! remove data -----------------------------
    delete sniper;
    delete aa;
    delete truck;
    delete mortar;
    delete regular;
    delete truck;
    delete truck1;
    delete regular1;
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}