#ifndef AP_SECONDMS_CELL_H
#define AP_SECONDMS_CELL_H

#include <ostream>

struct Cell {
public:
    int row;
    int column;

    bool operator==(const Cell &c) const {
        return (this->row == c.row) && (this->column == c.column);
    }

    bool operator<(const Cell &c) const {
        bool result = std::pair<int,int>(row,column) <
                std::pair<int,int>(c.row,c.column);
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell) {
        os << "row: " << cell.row << " column: " << cell.column;
        return os;
    }
    std:: string toString(){
        return "row" + std::to_string(this->row) + "column"+std::to_string
                (this->column);
    }
};

namespace std {
    template<>
    struct hash<Cell> {
        size_t operator()(const Cell &cell) const {
            size_t rowHash = hash<int>()(cell.row);
            size_t colHash = hash<int>()(cell.column);
            return rowHash ^ colHash;
        }
    };
}


#endif
