void replaceString(string s, string s1, string s2) {
    size_t pos = s.rfind(s1);
    if(pos != string::npos){
        s.replace(pos, s1.length(), s2);
    }
    cout << s; 
}

void deleteWord(string s, string s1){
    size_t pos = s.find(s1);
    while(pos  != string::npos){
        s.erase(pos, s1.length());
        pos = s.find(s1);
    }
    cout << s;
}