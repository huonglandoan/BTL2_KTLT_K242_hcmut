#include "BattleField.h"
//!-----------------------------------------------------
// CLASS BattleField
//!-----------------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    terrain = new TerrainElement**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        terrain[i] = new TerrainElement*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            Position pos(i, j);
            TerrainElement* elem = nullptr;

            // Kiểm tra từng loại terrain theo thứ tự ưu tiên
            for (auto& p : arrayForest)
                if (p->getRow() == i && p->getCol() == j) { elem = new Mountain(pos); break; }

            if (!elem) for (auto& p : arrayRiver)
                if (p->getRow() == i && p->getCol() == j) { elem = new River(pos); break; }

            if (!elem) for (auto& p : arrayFortification)
                if (p->getRow() == i && p->getCol() == j) { elem = new Fortification(pos); break; }

            if (!elem) for (auto& p : arrayUrban)
                if (p->getRow() == i && p->getCol() == j) { elem = new Urban(pos); break; }

            if (!elem) for (auto& p : arraySpecialZone)
                if (p->getRow() == i && p->getCol() == j) { elem = new SpecialZone(pos); break; }

            
            if (!elem) elem = new Road(pos);

            terrain[i][j] = elem;
        }
    }
}

BattleField::~BattleField() {
    for(int i = 0; i < n_rows; ++i){
        for(int j = 0; j < n_cols; ++j){
            delete terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
}

TerrainElement* BattleField::getElement(int r, int c) const {
    if(r >= 0 && r < n_rows && c >= 0 && c < n_cols){
        return terrain[r][c];
    }
    return nullptr;
}

string BattleField::str() const {
    stringstream ss;
    ss << "BattleField[n_rows=" << n_rows << ",n_cols=" << n_cols << "]";

    // for (int i = 0; i < n_rows; ++i) {
    //     for (int j = 0; j < n_cols; ++j) {
    //         // Kiểm tra loại địa hình và in ra ký hiệu tương ứng
    //         TerrainElement* element = terrain[i][j];
    //         if (element != nullptr) {
    //             switch (element->getTerrain()) {
    //                 case ROAD: ss << "ROA"; break;
    //                 case MOUNTAIN: ss << "MOU"; break;
    //                 case RIVER: ss << "RIV"; break;
    //                 case FORTIFICATION: ss << "FOR"; break;
    //                 case URBAN: ss << "URB"; break;
    //                 case SPECIAL_ZONE: ss << "SPE"; break;
    //                 default: ss << "UNK"; break; // Trường hợp mặc định nếu không có loại địa hình nào
    //             }
    //         } else {
    //             ss << "UNK"; // Nếu phần tử địa hình là null
    //         }

    //         // Thêm dấu cách giữa các cột, trừ cột cuối
    //         if (j < n_cols - 1) {
    //             ss << ' ';
    //         }
    //     }

    //     // Thêm dấu xuống dòng giữa các hàng, trừ hàng cuối cùng
    //     if (i < n_rows - 1) {
    //         ss << '\n';
    //     }
    // }

    return ss.str();
}
