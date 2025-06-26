#ifndef INFANTRY_H
#define INFANTRY_H

#include "Unit.h"

enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};
class Infantry : public Unit
{
protected:
    InfantryType infantryType;  // * Thể loại bộ binh
    bool isPerfectSquare(int a) const;
    int personalNumber(int num, int year) const;
    int attackScore = -1;
    int modifiedScore = -1;
    void init() {
        // Tính điểm ban đầu
        int tmpScore = static_cast<int>(infantryType) * 56 + quantity * weight;
        if (infantryType == SPECIALFORCES && isPerfectSquare(weight)) {
            tmpScore += 75;
        }

        int perNum = personalNumber(tmpScore, 1975);
        int q = quantity;

        // Điều chỉnh quantity duy nhất một lần
        if (perNum > 7) {
            q = safeCeil(quantity + quantity * 0.2);
        } else if (perNum < 3 && quantity > 1) {
            q = safeCeil(quantity - quantity * 0.1);
        }
       
        Unit::setQuantity(q);
         attackScore = calcScore(); // Lưu lại nếu cần dùng nhiều
    }

    int calcScore() const {
        int score = static_cast<int>(infantryType) * 56 + quantity * weight;
        return safeCeil(score);
    }
public:
    // * Constructor: khởi tạo với quantity, weight, pos và infantryType.
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType) {init();}
    // * Override hàm getAttackScore:
    // * score = (infantryType_value * 56) + (quantity * weight)
    // * Nếu infantryType là SPECIALFORCES và weight là số chính phương thì cộng thêm 75 điểm.
    // * Sau đó, dựa trên "số cá nhân" của score (với năm 1975):
    // *   - Nếu số cá nhân > 7: tăng 20% số lượng (làm tròn lên).
    // *   - Nếu số cá nhân < 3: giảm 10% số lượng (đảm bảo quantity không nhỏ hơn 1).
    int getAttackScore() override;
    InfantryType getInfantryType() const {return infantryType; }
    // * Override hàm str: trả về chuỗi theo định dạng
    // * "Infantry[infantryType=<infantryType>, quantity=<quantity>, weight=<weight>, pos=<pos>]"
    string str() const override;
    Unit *clone() const override{
        return new Infantry(getQuantity(), getWeight(), getCurrentPosition(), getInfantryType());
    }
    void setWeight(int w) override{
        Unit::setWeight(w);
        attackScore = calcScore();
    }
    void setQuantity(int q) override{
        Unit::setQuantity(q);
        attackScore = calcScore();
    }
    void setAttackScore(int score) {
        modifiedScore = score;
    }
    
    void resetAttackScore() {
        modifiedScore = -1;
    }
    
    
};

#endif // INFANTRY_H