#include "Configuration.h"

void processFile(const string &filename, TerrainType **&battlefield, int &NUM_ROWS, int &NUM_COLS, vector<UNIT_NAME> &units, int &EVENT_CODE) {
    ifstream fin(filename);
    if (!fin.is_open()) return;

    string line;
    vector<pair<string, vector<pair<int, int>>>> terrainData;
    vector<string> unitLines;
    EVENT_CODE = 0;
    NUM_ROWS = NUM_COLS = 0;
    bool hasRows = false, hasCols = false;

    const string terrainKeys[] = {"ARRAY_FOREST", "ARRAY_RIVER", "ARRAY_FORTIFICATION", "ARRAY_URBAN", "ARRAY_SPECIAL_ZONE"};
    const TerrainType terrainValues[] = {FOREST, RIVER, FORTIFICATION, URBAN, SPECIAL_ZONE};
    const int terrainCount = 5;

    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line.find("NUM_ROWS=") == 0) {
            NUM_ROWS = stoi(trim(line.substr(9)));
            hasRows = true;
        } else if (line.find("NUM_COLS=") == 0) {
            NUM_COLS = stoi(trim(line.substr(9)));
            hasCols = true;
        } else if (line.find("EVENT_CODE") == 0) {
            
             int code = stoi(trim(line.substr(line.find('=') + 1)));
             if(code >= 100){
                 code = code % 100;
            }else if(code < 0){
                code = 0;
            }
            EVENT_CODE = code; 
        } else if (line.find("UNIT_LIST=[") == 0) {
            while (getline(fin, line)) {
                line = trim(line);
                if (line == "]") break;
                if (!line.empty()) unitLines.push_back(line);
            }
        } else {
            for (int i = 0; i < terrainCount; ++i) {
                if (line.find(terrainKeys[i] + "=[") == 0) {
                    vector<pair<int, int>> coords;
                    size_t start = line.find('[') + 1;
                    size_t end = line.find(']');
                    string content = line.substr(start, end - start);
                    istringstream iss(content);
                    string coord;

                    while (getline(iss, coord, ')')) {
                        size_t left = coord.find('(');
                        if (left == string::npos) continue;
                        string pairStr = coord.substr(left + 1);
                        size_t comma = pairStr.find(',');
                        if (comma == string::npos) continue;
                        int x = stoi(trim(pairStr.substr(0, comma)));
                        int y = stoi(trim(pairStr.substr(comma + 1)));
                        coords.emplace_back(x, y);

                        if (!hasRows && x + 1 > NUM_ROWS) NUM_ROWS = x + 1;
                        if (!hasCols && y + 1 > NUM_COLS) NUM_COLS = y + 1;
                    }

                    terrainData.push_back({terrainKeys[i], coords});
                }
            }
        }
    }
    fin.close();

    // Cấp phát bản đồ mặc định là ROAD
    battlefield = new TerrainType*[NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; ++i) {
        battlefield[i] = new TerrainType[NUM_COLS];
        for (int j = 0; j < NUM_COLS; ++j)
            battlefield[i][j] = ROAD;
    }

    // Gán các ô địa hình
    for (const auto &entry : terrainData) {
        TerrainType type = ROAD;
        for (int i = 0; i < terrainCount; ++i) {
            if (entry.first == terrainKeys[i]) {
                type = terrainValues[i];
                break;
            }
        }

        for (const auto &pos : entry.second) {
            int x = pos.first, y = pos.second;
            if (x >= 0 && x < NUM_ROWS && y >= 0 && y < NUM_COLS)
                battlefield[x][y] = type;
        }
    }

    /// Xử lý đơn vị UNIT_LIST
for (const string &line : unitLines) {
    size_t typeEnd = line.find('(');
    if (typeEnd == string::npos) continue;

    string typeStr = trim(line.substr(0, typeEnd));
    string args = line.substr(typeEnd + 1);  // Không cắt gì thêm

    int qty, weight, x, y, army;

    if (sscanf(args.c_str(), "%d,%d,(%d,%d),%d", &qty, &weight, &x, &y, &army) != 5) {
        cerr << "ERROR parsing UNIT_LIST line (bad format): " << line << endl;
        continue;
    }

    InfantryType it;
    if (typeStr == "SNIPER") it = SNIPER;
    else if (typeStr == "ANTIAIRCRAFTSQUAD") it = ANTIAIRCRAFTSQUAD;
    else if (typeStr == "MORTARSQUAD") it = MORTARSQUAD;
    else if (typeStr == "ENGINEER") it = ENGINEER;
    else if (typeStr == "SPECIALFORCES") it = SPECIALFORCES;
    else it = REGULARINFANTRY;

    UNIT_NAME u;
    u.type = it;
    u.quantity = qty;
    u.weight = weight;
    u.position_x = x;
    u.position_y = y;
    u.armyBelong = (army == 1) ? 1 : 0;
    units.push_back(u);

    if (!hasRows && x + 1 > NUM_ROWS) NUM_ROWS = x + 1;
    if (!hasCols && y + 1 > NUM_COLS) NUM_COLS = y + 1;
}

}

string print_battlefield(const TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS) {
    ostringstream oss;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            switch (battlefield[i][j]) {
                case ROAD: oss << "ROA"; break;
                case FOREST: oss << "FOR"; break;
                case RIVER: oss << "RIV"; break;
                case URBAN: oss << "URB"; break;
                case SPECIAL_ZONE: oss << "SPE"; break;
                case FORTIFICATION: oss << "FOR"; break;
                default: oss << "UNK"; break;
            }
            // Không thêm dấu cách sau phần tử cuối cùng
            if (j != NUM_COLS - 1) oss << " ";
        }
        // Không thêm dòng mới sau dòng cuối cùng
        if (i != NUM_ROWS - 1) oss << '\n';
    }
    return oss.str();
}



string print_UNIT_NAME(const vector<UNIT_NAME>& units) {
    ostringstream oss;
    
    if (units.empty()) {
        oss << "[\n\n]"; // Trường hợp rỗng: in đúng theo định dạng yêu cầu
        return oss.str();
    }
    oss << "[\n";
    for (size_t i = 0; i < units.size(); ++i) {
        const auto& unit = units[i];
        oss << infantryTypeToString(unit.type)
            << "(" << unit.quantity
            << "," << unit.weight
            << ",(" << unit.position_x << "," << unit.position_y << ")"
            << "," << ((unit.armyBelong) ? "1" : "0") << ")";
        if (i != units.size() - 1) oss << ",";
        oss << "\n";
    }
    oss << "]";
    return oss.str();
}

void clearBattlefield(TerrainType **battlefield, const int &NUM_ROWS, const int &NUM_COLS) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        delete[] battlefield[i];
    }
    delete[] battlefield;
    battlefield = nullptr;
}


