/* 
void process(const char str[], char outstr[])
{
    bool newWord = true;
    int i = 0, j = 0;

    while(str[i] != '\0')
    {
        if(str[i] == ' ')
        {
            if(!newWord)
            {
                outstr[j++] = ' ';
                newWord = true;
            }
        }
            
        else if(str[i] >= 'A' && str[i] <= 'Z')
            {
                outstr[j++] = newWord ? str[i] : str[i] + 32;
                newWord = false;
            }
        else if(str[i] >= 'a' && str[i] <= 'z')
            {
                outstr[j++] = newWord ? str[i] - 32 : str[i];
                newWord = false;
            }
            ++i;
        }   
    if(j > 0 && outstr[j-1] == ' ')
    {
        j--;
        outstr[j] = '\0';
    }   
}
*/
void reverse(char str[])
{
    int size = strlen(str);
    for(int i = 0; i < size/2 ; ++i)
    swap(str[i], str[size - i - 1]);
}

void recover(char str[])
{
    int size = strlen(str);
    for(int i = 0; i < size; ++i)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        else if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }

}

int find(char str[], char substr[])
{   
   return (strstr(str,substr) == nullptr)? -1 : strstr(str,substr) - str;
}

void process1(const char *name, char *outstr)
{
    int i = 0;
    int j = 0;
    bool newWord = true;

    while(name[i] != '\0')
    {
        if(name[i] == ' ')
        {
            if(!newWord)
            {
                outstr[j++] = ' ';
                newWord = true;
            }            
        }
        else if(name[i] >= 'a' && name[i] <= 'z')
            {
                outstr[j++] = newWord? name[i] - 32: name[i];
                newWord = false;
            }
        else if(name[i] >= 'A' && name[i] <= 'Z')
            {
                outstr[j++] =  newWord? name[i]: name[i] + 32;
                newWord = false;
            }
        i++;
    }

    if(j > 0 && outstr[j-1] == ' ')
    {
        j--;
        outstr[j] = '\0';
    }
}
void printFirstRepeatedWord(char str[])
{
    int count = 0;
    char words[100][30];

    char *token = strtok(str, " ");
    while(token){
        for(int i = 0; i < count; ++i){
            if(strcmp(words[i], token) == 0){
                cout << token << endl;
                return;
            }
        }
        strcpy(words[count++], token);
        token = strtok(nullptr, " ");
    }
    cout << "No Repetition";
}

bool findName(string path, string name){
    string str = "";
    ifstream file(path);
    string line;

    while(getline(file, line)){
        str += line;
    }
   
    if(str.find(name) != string::npos)  return true;

    int i  = 0;
    int j = 0;
    string newStr = "";
    while(str[i] != '\0'){
        if(str[i] > 'A' && str[i] <= 'Z')
            newStr[j] = str[i] + 32;
        else newStr[j] = str[i];
        i++;
        j++;
    }
    int k = 0;
    while(name[k] != '\0'){
        if(name[k] > 'A' && name[k] <= 'Z')
            name[k] = name[k] + 32;
    }
   
    if(newStr.find(name) != string::npos)  return true;
        return false;
    }
    void process(char str[], char outstr[]){
        outstr[0] = '\0';
        char *token = strtok(str, " ");
        while(token){
            strcat(outstr, token);
            token = strtok(nullptr, " ");
            if(token)
                strcat(outstr, " ");
            
        }
    }