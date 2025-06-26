#ifndef utils
#define utils

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define BLUE "\033[0;34m"

#include "main.h"
#include "tay_nguyen_campaign.h"
using namespace std;

// RunTest

void getOutput(int i, string task = "ALL");
void runOutput(int a = 0, int b = 10, string task = "ALL");
void runTest(int a = 0, int b = 10, string task = "ALL");

// Utils
int sumArray(int LF[17]);
string printLF(int LF[17], int n);

// Reading input helper
void readTarget(const string &filename, string &s);
void readBattelField(const string &filename, int matrix[10][10]);
void readSuppy(const string &filename, int matrix[5][5], int &shortfall);
void compareFiles(const string& file1, const string& file2, string &task, int &file_idx);

// Implements
int sumArray(int LF[17]){
    int sum = 0;
    for(int i = 0; i < 17; i++){
        sum += LF[i];
    }
    return sum;
}

string printLF(int LF[17], int n){
    stringstream ss;
    ss << "LF" << n << "=[";
    for(int i = 0; i < 17; i++){
        ss << LF[i];
        if(i < 16){
            ss << ",";
        }
    }
    ss << "]" << endl;
    return ss.str();
}

void getOutput(int i, string task){
    
    if(task == "ALL"){
        string recursion[7] = {"TASK0", "TASK1", "TASK2_1", "TASK2_2", "TASK3", "TASK4", "TASK5"};
        for(auto it : recursion){
            getOutput(i, it);
        }
        return;
    }

    int LF1[17], LF2[17], EXP1, EXP2, T1, T2, E;
    int BattleField[10][10], Supply[5][5], shortfall;
    int sLF1 = sumArray(LF1), sLF2 = sumArray(LF2);
    string fake_target, true_target;

    if(!readFile("input/input_config/config" + to_string(i) + ".txt", LF1, LF2, EXP1, EXP2, T1, T2, E)){
        cout << "ReadFile can't run" << endl;
        return;
    }

    string output = "";
    string expected = "";
    
    if(task == "TASK0"){
        string strLF1 = printLF(LF1, 1), strLF2 = printLF(LF2, 2);

        output = "output/output_config/config" + to_string(i) + ".txt";
        //  expected = "expected/expected_config/config" + to_string(i) + ".txt";
        //  output = expected;
        
        ofstream out(output);
        
        out << strLF1 << strLF2
            << "EXP1=" << EXP1 << ", EXP2=" << EXP2 << endl
            << "T1=" << T1 << ", T2=" << T2 << endl
            << "E=" << E << endl;
    }
    else if(task == "TASK1"){
        int task1 = gatherForces(LF1, LF2);

        output = "output/output_gather_forces/gforces" + to_string(i) + ".txt";
        // expected = "expected/expected_gather_forces/gforces" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "GATHER_FORCES: " << task1 << endl;
    }
    else if(task == "TASK2_1"){
        readTarget("input/input_fake_target/ftarget" + to_string(i) + ".txt", fake_target);
        string task2_1 = determineRightTarget(fake_target);

        output = "output/output_fake_target/ftarget" + to_string(i) + ".txt";
        // expected = "expected/expected_fake_target/ftarget" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "DETERMINE_RIGHT_TARGET: " << task2_1 << endl;
    }
    else if(task == "TASK2_2"){
        readTarget("input/input_true_target/ttarget" + to_string(i) + ".txt", true_target);
        string task2_2 = decodeTarget(true_target, EXP1, EXP2);

        output = "output/output_true_target/ttarget" + to_string(i) + ".txt";
        // expected = "expected/expected_true_target/ttarget" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "DECODE_TARGET: " << task2_2 << endl;
    }
    else if(task == "TASK3"){
        int cloneT1 = T1, cloneT2 = T2;
        manageLogistics(sLF1, sLF2, EXP1, EXP2, cloneT1, cloneT2, E);

        output = "output/output_logistic/logistic" + to_string(i) + ".txt";
        // expected = "expected/expected_logistic/logistic" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "MANAGE_LOGISTICS: T1=" << cloneT1 << ", T2=" << cloneT2 << endl;
    }
    else if(task == "TASK4"){
        readBattelField("input/input_battlefield/battlefield" + to_string(i) + ".txt", BattleField);
        int task4 = planAttack(sLF1, sLF2, EXP1, EXP2, T1, T2, BattleField);

        output = "output/output_battlefield/battlefield" + to_string(i) + ".txt";
        // expected = "expected/expected_battlefield/battlefield" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "PLAN_ATTACK: " << task4 << endl;
    }
    else if(task == "TASK5"){
        readSuppy("input/input_supply/supply" + to_string(i) + ".txt", Supply, shortfall);
        int task5 = resupply(shortfall, Supply);

        output = "output/output_supply/supply" + to_string(i) + ".txt";
        // expected = "expected/expected_supply/supply" + to_string(i) + ".txt";
        // output = expected;

        ofstream out(output);

        out << "RESUPPLY: " << task5 << endl;
    }
    else{
        cout << "INCORRECTED TASK" << endl;
    }
    return;
}

void readTarget(const string &filename, string &s){
    ifstream file(filename);
    getline(file, s);
}

void readBattelField(const string &filename, int matrix[10][10]){
    ifstream file(filename);
    if(!file.is_open()){
        cout << YELLOW << "File " << filename << " is not opened" << RESET << endl;
        return;
    }
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            file >> matrix[i][j];
        }
    }
    
    file.close();
}

void readSuppy(const string &filename, int matrix[5][5], int &shortfall){
    ifstream file(filename);
    if(!file.is_open()){
        cout << YELLOW << "File " << filename << " is not opened" << RESET << endl;
        return;
    }
    
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            file >> matrix[i][j];
        }
    }

    file >> shortfall;
}

void runOutput(int a, int b, string task){
    for(int i = a; i < b; i++){
        getOutput(i, task);
    }
}

void runTest(int a, int b, string task){
    if(task == "ALL"){
        string recursion[7] = {"TASK0", "TASK1", "TASK2_1", "TASK2_2", "TASK3", "TASK4", "TASK5"};
        for(auto it : recursion){
            runTest(a, b, it);
        }
        return;
    }
    cout << BLUE << "__________START TESTING " << task << "__________" << RESET << endl;
    for(int i = a; i < b; i++){
        string output = "";
        string expected = "";

        if(task == "TASK0"){
            output = "output/output_config/config" + to_string(i) + ".txt";
            expected = "expected/expected_config/config" + to_string(i) + ".txt";
        }
        else if(task == "TASK1"){
            output = "output/output_gather_forces/gforces" + to_string(i) + ".txt";
            expected = "expected/expected_gather_forces/gforces" + to_string(i) + ".txt";
        }
        else if(task == "TASK2_1"){
            output = "output/output_fake_target/ftarget" + to_string(i) + ".txt";
            expected = "expected/expected_fake_target/ftarget" + to_string(i) + ".txt";
        }
        else if(task == "TASK2_2"){
            output = "output/output_true_target/ttarget" + to_string(i) + ".txt";
            expected = "expected/expected_true_target/ttarget" + to_string(i) + ".txt";
        }
        else if(task == "TASK3"){
            output = "output/output_logistic/logistic" + to_string(i) + ".txt";
            expected = "expected/expected_logistic/logistic" + to_string(i) + ".txt";
        }
        else if(task == "TASK4"){
            output = "output/output_battlefield/battlefield" + to_string(i) + ".txt";
            expected = "expected/expected_battlefield/battlefield" + to_string(i) + ".txt";
        }
        else if(task == "TASK5"){
            output = "output/output_supply/supply" + to_string(i) + ".txt";
            expected = "expected/expected_supply/supply" + to_string(i) + ".txt";
        }
        else{
            cout << "INCORRECTED TASK" << endl;
        }
        compareFiles(output, expected, task, i);
    }
    cout << BLUE << "__________END TESTING " << task << "__________" << RESET << endl;
}

void compareFiles(const string& file1, const string& file2, string &task, int &file_idx) {
    ifstream f1(file1);
    ifstream f2(file2);

    if(f1.is_open() && f2.is_open()){
        string line1, line2;
        while (getline(f1, line1) && getline(f2, line2)){
            if(line1 != line2){
                // cout << "Files are different!" << endl;
                cout << RED << "TESTCASE " << task << " " << file_idx << ": FAILED" << RESET << endl;

                return;
            }
        }
        cout << GREEN << "TESTCASE " << task << " " << file_idx << ": PASS" << RESET << endl;
    }
    else{
        cerr << YELLOW << ((!f1.is_open()) ? "OPENNING OUTPUT " : "OPENNING EXPECTED ") << task << " " << file_idx << " ERROR!" << RESET << endl;
    }
}

#endif