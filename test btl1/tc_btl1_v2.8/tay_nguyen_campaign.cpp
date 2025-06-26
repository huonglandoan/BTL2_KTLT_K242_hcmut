#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;


const int LF_MAX_VALUE = 1000;
const int EXP_MAX_VALUE = 600;
const int T_MAX_VALUE = 3000;
const int E_MAX_VALUE = 99;
const int MIN_VALUE = 0;
const int MAX_ID = 100;

const int Index[17] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 15, 18, 20, 30, 40, 50, 70};
// Task 0: Read input file
int max (int a, int b) { return a > b? a : b;}

int min (int a, int b) { return a < b? a : b;}

void checkLF (int LF1[], int LF2[]) {
  for(int i = 0; i < MAX_LINE_LENGTH; ++i)
  {
      LF1[i] = max(min(LF_MAX_VALUE, LF1[i]), MIN_VALUE);
      LF2[i] = max(min(LF_MAX_VALUE, LF2[i]), MIN_VALUE);
    }
}

void checkEXP (int &EXP1, int &EXP2)  {
  EXP1 = max(min(EXP_MAX_VALUE, EXP1), MIN_VALUE);
  EXP2 = max(min(EXP_MAX_VALUE, EXP2), MIN_VALUE);
}

void checkT (int &T1, int &T2) {
  T1 = max(min(T_MAX_VALUE, T1), MIN_VALUE);
  T2 = max(min(T_MAX_VALUE, T2), MIN_VALUE);
}

void checkE (int &E) {
  E = max(min(E_MAX_VALUE, E), MIN_VALUE);
}


bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }
  

  // TODO: Extract values from the `data` array and store them in respective variables

  stringstream ss;

  // LF1
  ss.str(data[0]);
  for(int i = 0; i < 17; ++i)
  {
    while(ss.peek() == '[' || ss.peek() == ']')
      ss.ignore();

      ss >> LF1[i];
      if(ss.peek() == ',')  
        ss.ignore();
  }
  ss.clear();

  // LF2
  ss.str(data[1]);
  for(int i = 0; i < 17; ++i)
  {
    while(ss.peek() == '[' || ss.peek() == ']')
      ss.ignore();

      ss >> LF2[i];
      if(ss.peek() == ',')
        ss.ignore();
  }
  ss.clear();

  // EXP1, EXP2
  ss.str(data[2]);
  ss >> EXP1 >> EXP2;
  ss.clear();

  // T1, T2
  ss.str(data[3]);
  ss >> T1 >> T2;
  ss.clear();

  // E
  ss.str(data[4]);
  ss >> E;
  ss.clear();

  checkE(E);
  checkT(T1, T2);
  checkEXP(EXP1, EXP2);
  checkLF(LF1, LF2);
  
  return true;
} 

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function
  checkLF(LF1, LF2);
  

  int lf1 = 0;
  int lf2 = 0;
  for(int i = 0; i < 17; ++i)
  {
      lf1 += LF1[i] * Index[i];
      lf2 += LF2[i] * Index[i];
  }
  return lf1 + lf2;
}

// Task 2

string ID[8] = {"Kon Tum","Pleiku", "Gia Lai", "Buon Ma Thuot","Duc Lap", "Dak Lak", "National Route 21", "National Route 14" };

bool isDigit(char c) {
  return (c >= '0' && c <= '9');
}

int findID(int numbers[], int count)
{
    if(count == 1)  {
      if(numbers[0] >= 3 && numbers[0] <= 7)
        return numbers[0];
      else if(numbers[0] >= 0 && numbers[0] <= 2)
        return -2; // DECOY;
    }
    else if(count == 2)
        return ((numbers[0] + numbers[1]) % 5 + 3);
    else if(count == 3)
      return((max(numbers[0],max(numbers[1], numbers[2])))) % 5 + 3;
    
  return -1; // INVALID
}
string determineRightTarget(const string &target)
{
  int numbers[MAX_ID];
  int count = 0;
  string res = "";
  for(int i = 0; i < target.size(); ++i)
  {
      if(isDigit(target[i]))
      numbers[count++]= target[i] - '0'; 
      else res += target[i];
  }
  
    
  // TODO: Implement this function
  if(findID(numbers, count) == -1)
      return "INVALID";
  else if(findID(numbers, count) == -2)
      return "DECOY";
  
  return ID[findID(numbers, count)];
}

bool isAlpha(char c)
{
  return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

string CaesarCipher(const string &message, int shift)
{
  string newCode = "";
  for(int i = 0; i < message.size(); ++i)
  {
    if(message[i] >= 'a' && message[i] <= 'z')
      newCode += (message[i] - 'a' + shift) % 26 + 'a';
    else if(message[i] >= 'A' && message[i] <= 'Z')
      newCode += (message[i] - 'A' + shift) % 26 + 'A';
    else if((message[i] >= '0' && message[i] <= '9') || message[i] == ' ')
      newCode += message[i];
    else return "INVALID";
  }
  return newCode;
}

string reverse(const string &message)
{
  string newCode = "";
  bool newWord = true;

  for(int i = message.size() - 1; i >= 0 ; --i)
  {
     if(message[i] == ' '  &&  newWord == false )
    {
      newWord = true;
      newCode += ' ';
    }
    else if(newWord)
    {
      newCode += (message[i] >= 'a' && message[i] <= 'z') ? message[i] - 32 : message[i];  
      newWord = false;
    }
    else newCode += (message[i] >= 'A' && message[i] <= 'Z') ? message[i] + 32 : message[i];
  }
  return newCode;
}
string decodeTarget(const string &message, int EXP1, int EXP2)
{
  checkEXP(EXP1, EXP2);
  string newCode ="";
  // TODO: Implement this function
  // CaesarCipher
  if(EXP1 >= 300 && EXP2 >= 300)
  {
      int shift = (EXP1 + EXP2) % 26; 

      newCode = CaesarCipher(message, shift);
      return newCode;
  }
  else  
  {   
    newCode = reverse(message);
  }

  for(int i = 3; i <= 7; ++i)
      {
        if(ID[i] == newCode)
          return ID[i];
      }

  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  //checkLF(LF1, LF2);
  checkE(E);
  checkEXP(EXP1, EXP2);
  checkT(T1, T2);

  cout<< "-------------------------\n"; 
  cout << "LF1: " << LF1 << ", LF2: " << LF2 << endl;
  cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << endl;
  cout << "T1: " << T1 << ", T2: " << T2 << endl;
  cout << "E: " << E << endl; 

  int t1;
  int t2;

    if(E == 0)
    {
      t1 =  static_cast<int>((static_cast<double>((LF1 / (LF1 + LF2)))*(T1 + T2))*(1 +  static_cast<int>(((EXP1 - EXP2) / 100))));
      t2 = (T1 + T2) - t1;
      
      T1 += t1;
      T2 += t2;

      checkT(T1, T2);
    }
    else if(E >= 1 && E <= 9)
    {
      
       T1 = T1 - static_cast<int>((E*1.0 /100.0) * T1 + 0.5);
       T2 = T2 - static_cast<int>((E*0.5 / 100.0) * T2 + 0.5);
    }
    else if(E >= 10 && E <= 29)
    {
      T1 += (E*50);
      T2 += (E*50);
    }
    else if(E >= 30 && E <= 59)
    {
      T1 += static_cast<int>((E*0.005)*T1);
      T1 += static_cast<int>((E*0.002)*T2);
    }
    checkT(T1, T2);
    cout << "Task 3: " << T1 << " " << T2 << endl;
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  
  double S = (LF1 + LF2) + (EXP1 + EXP2) * 5 + (T1 + T2) *2;
  for(int i = 0; i < 10; ++i)
  {
    for(int j = 0; j < 10; ++j)
    {
       if(i % 2 == 0)
       {
        S = S - (battleField[i][j] * 2.0 / 3.0);
       }
       else {
        S = S - (battleField[i][j] * 3.0 / 2.0);
       }
    }
  }
  return ceil(S);
}

// Task 5
void swap(int a, int b)
{
  int x = a;
  a = b; 
  b = a;
}

int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int minSum = INT_MAX;
  int supplies[25];

  int idx = 0;
  for(int i = 0; i < 5; ++i)
  {
    for(int j = 0; j < 5; ++j)
      supplies[idx++] = supply[i][j];
  }

  for(int i = 0; i < 24; ++i)
  {
    if(supplies[i] < supplies[i+1])
      swap(supplies[i], supplies[i+1]);
  }

  for(int i = 0; i < 21; ++i){
    for(int j = i + 1; j < 22; ++j){
      for(int k = j + 1; k < 23; ++k){
        for(int l = k + 1; l < 24; ++l){
          for(int m = l + 1; m < 25; ++m){
            int curSum = supplies[i] + supplies[j] + supplies[k] + supplies[l] + supplies[m];
            if(curSum >= shortfall)
              minSum = min(minSum, curSum);
          }
        }
      }
    }
  }
  return minSum;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
