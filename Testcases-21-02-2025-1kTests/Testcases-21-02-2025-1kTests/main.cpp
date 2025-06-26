/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2025
* Date: 07.02.2025
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "tay_nguyen_campaign.h"

/*
 * Using this compile line to run the main.cpp. It is essential to read all the text below to use our testcases properly.
 *
 * If you find any mistakes or perhaps something is wrong with the expected, do not hesitate to contact our Facebook DM.
 *
 * To get your output (Getting all your output), if ";" causes error, replace it by "&&"
 * g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11; ./main RunOutput
 * 
 * To check your output (Checking all your output), if ";" causes error, replace it by "&&"
 * g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11; ./main RunTest
 * 
 * Optionally, to (get or check) your output of TASK... form a to (b - 1) by using this command line, if ";" causes error, replace it by "&&"
 * g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11; ./main (RunOutput or RunTest) TASK0 a b
 * 
 * a and b is just an integer, TASK is ALL by default but if you get output from a to b, TASK will be obligated to have value
 * TASK's value might be one of the following:
 * TASK0 for Task 0's output (in folder named .../..._config/config...)
 * TASK1 for Task 1's output (in folder named .../..._gather_forces/gforces...)
 * TASK2_1 for Task 2_1's output (in folder named .../..._fake_target/ftarget...)
 * TASK2_2 for Task 2_2's output (in folder named .../..._true_target/ttarget...)
 * TASK3 for Task 3's output (in folder named .../..._logistic/logistic...)
 * TASK4 for Task 4's output (in folder named .../..._battlefield/battlefield...)
 * TASK5 for Task 5's output (in folder named .../..._supply/supply...)
 */

#include "utils.h"

using namespace std;

int main(int argc, const char** argv){
    string MODE = argv[1];
    string TASK = "ALL";
    int a = 0, b = 1000;

    if(argc == 3){
        TASK = argv[2];
    }
    else if(argc == 5){
        TASK = argv[2];
        string strNum = argv[3];
        a = stoi(strNum);
        strNum = argv[4];
        b = stoi(strNum);
    }

    if(MODE == "RunOutput"){
        runOutput(a, b, TASK);
    }
    else if(MODE == "RunTest"){
        runTest(a, b, TASK);
    }
    return 0;
}
