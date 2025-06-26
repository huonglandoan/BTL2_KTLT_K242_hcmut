#include "main.h"                // chứa các #include cần thiết
#include "tay_nguyen_campaign.h" // khai báo prototype các hàm Task 1..5

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>

using namespace std;

// Hàm so sánh 2 file text, trả về true nếu giống y hệt, false nếu khác
bool compareFiles(const string &file1, const string &file2)
{
    ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open())
    {
        cerr << "Cannot open file to compare: " << file1 << " or " << file2 << endl;
        return false;
    }
    stringstream ss1, ss2;
    ss1 << f1.rdbuf();
    ss2 << f2.rdbuf();
    return (ss1.str() == ss2.str());
}

// Hàm kiểm tra ký tự không phải khoảng trắng
bool notSpace(unsigned char ch)
{
    return !std::isspace(ch);
}

int main()
{
    int numDifferences = 0;
    vector<int> diffIDs; // Lưu danh sách testcase bị khác

    for (int i = 0; i < 400; i++)
    {
        // Tạo tên file testcase: "testcase/000.txt", "testcase/001.txt", ...
        ostringstream tcin;
        tcin << "testcase/" << setw(3) << setfill('0') << i << ".txt";
        string inFile = tcin.str();

        // Tạo tên file output: "output/000.txt", ...
        ostringstream tcout;
        tcout << "output/" << setw(3) << setfill('0') << i << ".txt";
        string outFile = tcout.str();

        // Tạo tên file answer: "answer/000.txt", ...
        ostringstream tcan;
        tcan << "answer/" << setw(3) << setfill('0') << i << ".txt";
        string ansFile = tcan.str();

        // Mở file testcase
        ifstream fin(inFile);
        if (!fin.is_open())
        {
            cerr << "Cannot open testcase file " << inFile << endl;
            continue;
        }

        // Mở file output
        ofstream fout(outFile);
        if (!fout.is_open())
        {
            cerr << "Cannot open output file " << outFile << endl;
            fin.close();
            continue;
        }

        // -----------------------------
        // CHẠY TỪNG TASK THEO NHÓM CHỈ SỐ
        // -----------------------------
        if (i >= 0 && i < 50)
        {
            // ======= TASK 1 (gatherForces) =======
            // Định dạng testcase: 2 dòng, mỗi dòng chứa 17 số cho LF1 và LF2.
            int LF1[17], LF2[17];
            for (int j = 0; j < 17; j++)
            {
                fin >> LF1[j];
            }
            for (int j = 0; j < 17; j++)
            {
                fin >> LF2[j];
            }
            int result = gatherForces(LF1, LF2);
            fout << result << endl;
        }
        else if (i >= 50 && i < 150)
        {
            // ======= TASK 2 =======
            // Định dạng testcase: 2 phần
            // (a) 1 dòng: target cho determineRightTarget.
            // (b) 1 dòng: EXP1 EXP2 message
            {
                // Đọc dòng chứa target (phần a)
                string targetLine;
                if (!getline(fin, targetLine))
                {
                    cerr << "Error reading target from " << inFile << endl;
                }
                // Gọi determineRightTarget
                string result1 = determineRightTarget(targetLine);
                fout << result1 << endl;
            }
            {
                // Đọc dòng chứa EXP1 EXP2 message (phần b)
                string line;
                if (!getline(fin, line))
                {
                    cerr << "Error reading EXP and message from " << inFile << endl;
                }
                istringstream iss(line);
                int exp1, exp2;
                iss >> exp1 >> exp2;
                string message;
                getline(iss, message); // Lấy phần còn lại của dòng sau 2 số
                // Loại bỏ khoảng trắng đầu của message
                message.erase(message.begin(), find_if(message.begin(), message.end(), notSpace));
                string result2 = decodeTarget(message, exp1, exp2);
                fout << result2 << endl;
            }
        }
        else if (i >= 150 && i < 200)
        {
            // ======= TASK 3 (manageLogistics) =======
            int LF1, LF2, EXP1, EXP2, T1, T2, E;
            fin >> LF1 >> LF2 >> EXP1 >> EXP2 >> T1 >> T2 >> E;
            if (fin.fail()) {
                cerr << "Error reading data from " << inFile << endl;
                fin.close();
                fout.close();
                continue;
            }
            manageLogistics(LF1, LF2, EXP1, EXP2, T1, T2, E);
            cout << "Task 3: " << T1 << " " << T2 << endl;
            fout << T1 << " " << T2 << endl;
            
        }
        else if (i >= 200 && i < 250)
        {
            // ======= TASK 4 (planAttack) =======
            int LF1, LF2, EXP1, EXP2, T1, T2;
            fin >> LF1 >> LF2 >> EXP1 >> EXP2 >> T1 >> T2;
            int battleField[10][10];
            for (int r = 0; r < 10; r++)
            {
                for (int c = 0; c < 10; c++)
                {
                    fin >> battleField[r][c];
                }
            }
            int result = planAttack(LF1, LF2, EXP1, EXP2, T1, T2, battleField);
            fout << result << endl;
        }
        else
        {
            // ======= TASK 5 (resupply) =======
            int shortfall;
            fin >> shortfall;
            int supply[5][5];
            for (int r = 0; r < 5; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    fin >> supply[r][c];
                }
            }
            int ans = resupply(shortfall, supply);
            fout << ans << endl;
        }

        fin.close();
        fout.close();

        // So sánh file output với file answer
        if (!compareFiles(outFile, ansFile))
        {
            numDifferences++;
            diffIDs.push_back(i);
        }
    }

    cout << "Number of differences: " << numDifferences << endl;
    if (!diffIDs.empty())
    {
        cout << "Testcases differ:" << endl;
        for (int id : diffIDs)
        {
            cout << setw(3) << setfill('0') << id << ".txt" << endl;
        }
    }

    return 0;
}
