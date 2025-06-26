#include "UnitList.h"
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
UnitList::UnitList(int S) : count(0), head(nullptr), tail(nullptr)
{
    // TODO: Implement
    capacity = (isSpecial(S)) ? 12 : 8;
}
UnitList::~UnitList() {
    Node *cur = head;
    while(cur){
        Node *temp = cur;
        cur =  cur->next;
        delete temp;
    }
}
Unit* UnitList::findVehicle(VehicleType type){
    Node *cur = head;
    while(cur){
        Vehicle *v = dynamic_cast<Vehicle*>(cur->unit);

        if(v && v->getVehicleType() == type){
            return v;
        }
        cur = cur->next;
    }
    return nullptr;
}

Unit* UnitList::findInfantry(InfantryType type){
    Node *cur = head;
    while(cur){
        Infantry *i = dynamic_cast<Infantry*>(cur->unit);

        if(i && i->getInfantryType() == type){
            return i;
        }
        cur = cur->next;
    }
    return nullptr;
}
void UnitList::addUnit(Unit *u){
    if(count >= capacity)
        return;

    if(Infantry *i = dynamic_cast<Infantry*>(u)){
        Unit *found = findInfantry(i->getInfantryType());
        if(found){
            found->increaseQuantity(i->getQuantity());
           // i->setQuantity(i->getQuantity());
            return;
        }

        Node *newNode = new Node(i);
        newNode->next = head;
        head = newNode;

        if(tail == nullptr) tail = newNode;
        count++;
    }else if(Vehicle *v = dynamic_cast<Vehicle*>(u)){
        Unit *found = findVehicle(v->getVehicleType());
        if(found){
            found->increaseQuantity(u->getQuantity());
           // v->setQuantity(v->getQuantity());
            return;
        }

        Node *newNode = new Node(v);
        if(tail){
            tail->next = newNode;
            tail = newNode;
        }else{
            head = tail = newNode;
        }
        count++;
    }
}
bool UnitList::insert(Unit *unit)
{
   if (count >= capacity)
    return false;

   int oldCount = count;

   addUnit(unit);
   
   return count > oldCount;
}

void UnitList::insertToTail(Unit* unit) {
    Node* node = new Node(unit);
    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    count++;
}


bool UnitList::isContain(InfantryType infantryType)
{
   return  findInfantry(infantryType) == nullptr ? false : true;
}


bool UnitList::isContain(VehicleType vehicleType)
{
    return  findVehicle(vehicleType) == nullptr ? false : true;

}

string UnitList::str() const
{
    ostringstream oss;
    oss << "UnitList[count_vehicle=" << countV()
        << ";count_infantry=" << countI();

    Node *cur = head;
    if (cur) {
        oss << ";";  
        while (cur) {
            oss << cur->unit->str();
            if (cur->next)
                oss << ",";
            cur = cur->next;
        }
    }

    oss << "]";
    return oss.str();
}

void UnitList::CheckAndRemove(){
    Node *cur = head;
    Node *prev = nullptr;

    while(cur){
        Unit *u = cur->unit;

        if(u && u->getQuantity() <= 0){
            if(prev == nullptr){
                head = cur->next;
            }else{
                prev->next = cur->next;
            }

            if(cur == tail){
                tail = prev;
            }

            delete cur->unit;
            delete cur;
            count--;

            cur = (prev == nullptr) ? head : prev->next;
        }else{
            prev = cur;
            cur = cur->next;
        }
    }
 }

int UnitList::countV() const{
    int result = 0;
    Node *cur = head;
    while (cur) {
        if (dynamic_cast<Vehicle*>(cur->unit)) {
            result++;
        }
        cur = cur->next;
    }
    return result;
}

int UnitList::countI() const{
    int result = 0;
    Node *cur = head;
    while (cur) {
        if (dynamic_cast<Infantry*>(cur->unit)) {
            result++;
        }
        cur = cur->next;
    }
    return result;
}

void UnitList::remove(Unit *unit) {
    Node *cur = head;
    Node *prev = nullptr;

    while (cur) {
        if (cur->unit == unit) {
            if (prev == nullptr) {
                // Node cần xóa là head
                head = cur->next;
            } else {
                prev->next = cur->next;
            }

            if (cur == tail) {
                // Node cần xóa là tail
                tail = prev;
            }

            //delete cur->unit;
            delete cur;
            count--;
            return; // chỉ xóa 1 đơn vị đầu tiên tìm thấy
        }

        prev = cur;
        cur = cur->next;
    }
}

vector<Unit *> UnitList::getUnits() const{
    vector<Unit*> res;
    Node *cur = head;
    while(cur){
        res.push_back(cur->unit);
        cur = cur->next;
    }
    return res;
}

vector<Unit*> UnitList::getInfantryUnits() const{
    vector<Unit*> result;
    Node *cur = head;
    while (cur) {
        if (Infantry *i = dynamic_cast<Infantry*>(cur->unit)) {
            result.push_back(i); // lưu con trỏ Infantry
        }
        cur = cur->next;
    }
    return result;
}

vector<Unit*> UnitList::getVehicleUnits() const {
    vector<Unit*> result;
    Node *cur = head;
    while (cur) {
        if (Vehicle *v = dynamic_cast<Vehicle*>(cur->unit)) {
            result.push_back(v); // lưu con trỏ Vehicle
        }
        cur = cur->next;
    }
    return result;
}
