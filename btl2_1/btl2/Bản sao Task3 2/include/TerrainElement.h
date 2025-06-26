#ifndef _H_TERRAIN_ELEMENT_H_
#define _H_TERRAIN_ELEMENT_H_

class Army; // Forward declaration

#include "Army.h"

//-----------------------------------------------------
// CLASS TerrainElement và các lớp dẫn xuất
//-----------------------------------------------------
enum TerrainType
{
    ROAD,
    MOUNTAIN,
    RIVER,
    FORTIFICATION,
    URBAN,
    SPECIAL_ZONE
};
class TerrainElement {
protected:
    Position pos; // Vị trí của yếu tố địa hình
    // Phương thức tính khoảng cách giữa hai vị trí
    TerrainType terrain;
    double calculateDistance(const Position& pos1, const Position& pos2) {
        int rowDiff = pos1.getRow() - pos2.getRow();
        int colDiff = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
    }
    int safeCeil(double value) {
        double diff = abs(value - round(value));
        return (diff < 1e-9) ? round(value) : ceil(value);
    }
public:
    TerrainElement(Position pos, TerrainType terrainType = ROAD);
    virtual ~TerrainElement();
    // Phương thức thuần ảo: áp dụng hiệu ứng của yếu tố địa hình lên các quân đội.
    // (Chú ý: dùng tham số kiểu Army** theo đề bài.)
    virtual void getEffect(Army *army) = 0;
    TerrainType getTerrain() {return terrain; }
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos, ROAD) {}
    // Đường mòn không có hiệu ứng
    void getEffect(Army *army) override;
};
class Mountain : public TerrainElement {
    public:
    Mountain(Position pos) : TerrainElement(pos, MOUNTAIN ) {}
    
        // Rừng: hiệu ứng áp dụng
        void getEffect(Army *army) override;
            // Áp dụng tác động với cả các đơn vị bộ binh và phương tiện
        
    };
class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos, RIVER) {}
// Sông: hiệu ứng giảm EXP 10% cho lực lượng bộ binh nếu nằm trong bán kính 2 đơn vị (stub)
    void getEffect(Army *army) override;
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos, URBAN) {}
// Khu dân cư: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos, FORTIFICATION) {}
// Chiến hào: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos, SPECIAL_ZONE) {}
// Khu vực phi quân sự: hiệu ứng (stub) – đặt attackScore của các đơn vị xung quanh về 0
    void getEffect(Army *army) override;
};

#endif