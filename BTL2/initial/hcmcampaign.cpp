#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////
// Unit::~Unit() {}

Position::Position(const string &str_pos)
{
    char ch1, ch2, ch3;
    stringstream ss(str_pos);
    if (!(ss >> ch1 >> r >> ch2 >> c >> ch3) || ch1 != '(' || ch2 != ',' || ch3 != ')')
        r = c = -1;

} // Example: str_pos = "(1,15)"
Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : name(name), battleField(battleField), LF(0), EXP(0)
{

    UnitList *unitList = new UnitList(size);

    for (int i = 0; i < size; ++i)
    {
        if (!unitArray[i])
            continue;

        unitList->insert(unitArray[i]);

        if (unitArray[i]->isVehicle())
        {
            LF += unitArray[i]->getAttackScore();
        }
        else if (!unitArray[i]->isVehicle())
        {
            EXP += unitArray[i]->getAttackScore();
        }
    }

    // LF = clampValue(LF, 0, 1000);
    // EXP = clampValue(EXP, 0, 500);
}
string Vehicle::str() const
{
    ostringstream oss;
    oss << "["
        << "Vehicle[vehicleType=" << vehicleType // sua sau
        << ", quantity=" << quantity
        << ", weight=" << weight
        << ", pos=" << pos.str()
        << "]";

    return oss.str();
}
bool Infantry::isPerfectSquare(int a) const
{
    int num = (int)sqrt(a);
    return (num * num == a) ? true : false;
}

int Infantry::personalNumber(int num, int year) const
{
    int sum = num + 1975;
    while (sum >= 10)
    {
        int nsum = 0;
        while (sum > 0)
        {
            nsum += sum % 10;
            sum /= 10;
        }
        sum = nsum;
    }

    int yearSum = year;
    while (yearSum >= 10)
    {
        int nsum = 0;
        while (yearSum > 0)
        {
            nsum += yearSum % 10;
            yearSum /= 10;
        }
        yearSum = nsum;
    }
    return sum + yearSum;
}
int Infantry::getAttackScore()
{
    int score = static_cast<int>(infantryType) * 56 + quantity * weight;

    if (infantryType == SPECIALFORCES && isPerfectSquare(weight))
        score += 75;

    int perNum = personalNumber(score, 1975);

    if (perNum > 7)
        quantity += (quantity * 20) / 100;
    else if (perNum < 3)
        quantity -= (quantity * 10) / 100;

    return static_cast<int>(infantryType) * 56 + quantity * weight;
}

string Infantry::str() const
{
    ostringstream oss;
    oss << "["
        << "InfantryType[infantryType=" << infantryType // sua sau
        << ", quantity=" << quantity
        << ", weight=" << weight
        << ", pos=" << pos.str()
        << "]";
    return oss.str();
}

bool UnitList::isSpecial(int n) const
{
    int bases[] = {3, 5, 7};
    for (int base : bases)
    {
        int sum = 0, power = 1;
        while (sum < n)
        {
            sum += power;
            if (sum == 0)
                return true;
            power *= base;
        }
    }
    return false;
}
vector<Position *> Configuration::parsePositions(const string &input)
{
    vector<Position *> pos;

    if (input.length() < 2)
        return pos;

    stringstream ss(input.substr(1, input.length() - 2)); // bỏ 2 dấu ngoặc []
    string token;

    while (getline(ss, token, ','))
    {
        size_t openParen = token.find('(');
        size_t comma = token.find(',');
        size_t closeParen = token.find(')');

        if (openParen == string::npos || comma == string::npos || closeParen == string::npos)
            continue;

        int r = stoi(token.substr(openParen, closeParen - comma - 1));
        int c = stoi(token.substr(comma + 1, closeParen - comma - 1));

        pos.push_back(new Position(r, c));
    }
    return pos;
}
vector<string> splitUnit(const string &input, char deter)
{
    vector<string> List;
    string unitBuffer = "";
    string token;
    int cB = 0;
    for (char c : input)
    {
        if (c == '(')
            cB++;
        if (c == ')')
            cB--;

        if (c == deter && cB == 0)
        {
            List.push_back(unitBuffer);
            unitBuffer.clear();
        }
        else
        {
            unitBuffer += c;
        }
    }
    if (!unitBuffer.empty())
        List.push_back(unitBuffer);
    return List;
}

void Configuration::parseUnits(const string &input)
{
    if (input.length() < 2)
    {
        libsize = 0;
        ARVNsize = 0;
        liberationUnits = nullptr;
        ARVNUnits = nullptr;
        return;
    }

    vector<Unit *> liberationList;
    vector<Unit *> ARVNList;

    string content = input.substr(1, input.length() - 2); // Bỏ dấu []
    vector<string> Utoken = splitUnit(content, ',');

    // Duyệt từng đơn vị trong danh sách
    for (string &token : Utoken)
    {
        size_t openParen = token.find('(');
        if (openParen == string::npos)
            continue;

        string unitType = token.substr(0, openParen);
        string params = token.substr(openParen + 1, token.length() - openParen - 2);
        vector<string> paramsList = splitUnit(params, ',');

        if (paramsList.size() == 4)
        {
            int quantity = stoi(paramsList[0]);
            int weight = stoi(paramsList[1]);
            Position pos = Position(paramsList[2]);
            int armyBelong = stoi(paramsList[3]);

            Unit *newUnit = nullptr;
            if (isInfantryType(unitType))
                newUnit = new Infantry(quantity, weight, pos, getInfantryType(unitType));
            else if (isVehicleType(unitType))
                newUnit = new Vehicle(quantity, weight, pos, getVehicleType(unitType));

            if (newUnit)
            {
                if (armyBelong == 0)
                    liberationList.push_back(newUnit);
                else if (armyBelong == 1)
                    ARVNList.push_back(newUnit);
            }
        }
    }
    libsize = liberationList.size();
    ARVNsize = ARVNList.size();

    liberationUnits = (libsize > 0) ? new Unit *[libsize] : nullptr;
    ARVNUnits = (ARVNsize > 0) ? new Unit *[ARVNsize] : nullptr;

    for (int i = 0; i < libsize; ++i)
    {
        liberationUnits[i] = liberationList[i];
    }

    for (int i = 0; i < ARVNsize; ++i)
    {
        ARVNUnits[i] = ARVNList[i];
    }
}

Configuration::Configuration(const string &filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cout << "Not open this file \n";
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        size_t eq_pos = line.find('=');
        if (eq_pos == string::npos)
            continue;

        string key = line.substr(0, eq_pos);
        string value = line.substr(eq_pos + 1);

        if (key == "NUM_ROWS")
        {
            num_rows = stoi(value);
        }
        else if (key == "NUM_COLS")
        {
            num_cols = stoi(value);
        }
        else if (key == "ARRAY_FOREST")
        {
            arrayForest = parsePositions(value);
        }
        else if (key == "ARRAY_RIVER")
        {
            arrayRiver = parsePositions(value);
        }
        else if (key == "ARRAY_FORTIFICATION")
        {
            arrayFortification = parsePositions(value);
        }
        else if (key == "ARRAY_URBAN")
        {
            arrayUrban = parsePositions(value);
        }
        else if (key == "ARRAY_SPECIAL_ZONE")
        {
            arraySpecialZone = parsePositions(value);
        }
        else if (key == "UNIT_LIST")
        {
            parseUnits(value);
            // Army(liberationUnits, libsize, "mimi", *battleField);
        }
        else if (key == "EVENT_CODE ")
        {
            if (stoi(value) >= 0 && stoi(value) <= 99)
                eventCode = stoi(value);
            else
                eventCode = (stoi(value) < 0) ? 0 : (stoi(value) % 100);
        }
    }
    file.close();
}

Configuration::~Configuration()
{
    if (liberationUnits)
    {
        for (int i = 0; i < libsize; ++i)
            delete liberationUnits[i];
        delete[] liberationUnits;
    }

    if (ARVNUnits)
    {
        for (int i = 0; i < ARVNsize; ++i)
            delete ARVNUnits[i];
        delete[] ARVNUnits;
    }
}

string Configuration::str() const
{
    stringstream oss;
    oss << "Configuration[\n",
        oss << "num_rows=" << num_rows << ", num_cols=" << num_cols << "\n";
    oss << "eventCode=" << eventCode << "\n";
    oss << "Forest=[";
    for (size_t i = 0; i < arrayForest.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << arrayForest[i]->str();
    }
    oss << "]\n";

    oss << "River=[";
    for (size_t i = 0; i < arrayRiver.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << arrayRiver[i]->str();
    }
    oss << "]\n";
    oss << "Fortification=[";
    for (size_t i = 0; i < arrayFortification.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << arrayFortification[i]->str();
    }
    oss << "]\n";

    oss << "Urban=[";
    for (size_t i = 0; i < arrayUrban.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << arrayUrban[i]->str();
    }
    oss << "]\n";

    oss << "SpecialZone=[";
    for (size_t i = 0; i < arraySpecialZone.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << arraySpecialZone[i]->str();
    }
    oss << "]\n";
    oss << "LiberationUnits=[";
    for (int i = 0; i < libsize; ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << liberationUnits[i]->str();
    }
    oss << "]\n";

    oss << "ARVNUnits=[";
    for (int i = 0; i < ARVNsize; ++i)
    {
        if (i > 0)
            oss << ", ";
        oss << ARVNUnits[i]->str();
    }
    oss << "]\n";
    oss << "]";

    return oss.str();
}

bool UnitList::insert(Unit *unit)
{
    if (unit == nullptr || count >= capacity)
        return false;

    Node *newNode = new Node(unit);
    newNode->next = nullptr;

    if (unit->isVehicle())
    {
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    else
    {
        newNode->next = head;
        head = newNode;
        if (!tail)
            tail = newNode;
    }
    count++;
    return true;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->unit->isVehicle())
        {
            Vehicle *cur = static_cast<Vehicle *>(temp->unit);
            if (cur->getVehicleType() == vehicleType)
                return true;
        }
        temp = temp->next;
    }
    return false;
} // return true if it exists
bool UnitList::isContain(InfantryType infantryType)
{
    Node *temp = head;
    while (temp)
    {
        if (!temp->unit->isVehicle())
        {
            Infantry *cur = static_cast<Infantry *>(temp->unit);
            if (cur->getInfantryType() == infantryType)
                return true;
        }
        temp = temp->next;
    }
    return false;
} // return true if it exists
string UnitList::str() const
{
    int cV = 0;
    int cI = 0;

    Node *temp = head;
    while (temp)
    {
        if (temp->unit->isVehicle())
            cV++;
        else
            cI++;
        temp = temp->next;
    }

    stringstream oss;
    oss << "UnitList[count_vehicle="
        << cV << ";count_infantry="
        << cI << ";";

    temp = head;
    bool first = true;

    while (temp)
    {
        if (!first)
            oss << ",";
        oss << temp->unit->str();
        first = false;
        temp = temp->next;
    }
    oss << "]";

    return oss.str();
}
UnitList::~UnitList()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp->unit;
        delete temp;
    }
    tail = nullptr;
    count = 0;
    capacity = 0;
}
void LiberationArmy::fight(Army *enemy, bool defense = false)
{
    if (defense == false)
    {
        // LF = clampValue(static_cast<int>(LF * 1.5), 0, 1000);
        // EXP = clampValue(static_cast<int>(EXP * 1.5), 0, 500);
    }
}
string LiberationArmy::str() const { return "hi"; }

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////