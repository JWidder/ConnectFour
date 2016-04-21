#include "ConnectFour.hpp"
#include "gsl_assert.h"
#include <algorithm>

using namespace tlCF;

uint32_t tlCF::GetMask(uint32_t bitPosition) {
    Expects(bitPosition < 31);
    uint32_t result = 0b11 << bitPosition;
    return result;
}

Board::FieldPosition tlCF::Board::CalculateFieldPosition(const uint32_t row, const uint32_t collumn) const {
    Expects(row < row_count);
    Expects(collumn < collumn_count);
    auto field_index = collumn*row_count + row;
    auto bit_index = field_index * 2;
    FieldPosition result = { bit_index / 32, bit_index % 32 };
    Ensures(result.array_index < 3);
    Ensures(result.position < 31);
    return result;
}

BoardFieldStatus tlCF::Board::GetStatus(FieldPosition position) const {
    auto result = (data_[position.array_index] & GetMask(position.position)) >> position.position;
    Ensures(result == empty || result == yellow || result == red);
    return static_cast<BoardFieldStatus>(result);
}

void tlCF::Board::WritePosition(FieldPosition pos, BoardFieldStatus color) {
    Expects(GetStatus(pos) == empty);
    Expects(color != empty);
    data_[pos.array_index] |= data_[pos.array_index] | (static_cast<uint32_t>(color) << pos.position);
}

VictoryStatus tlCF::Board::TestRows() const {
    //test all rows
    for (unsigned int i = 0; i < row_count; ++i) {
        for (unsigned int k = 0; k < collumn_count - 4; ++k) {
            if (GetStatus(i, k) != empty &&
                    GetStatus(i, k) == GetStatus(i, k + 1) &&
                    GetStatus(i, k) == GetStatus(i, k + 2) &&
                    GetStatus(i, k) == GetStatus(i, k + 3)) {
                return static_cast<VictoryStatus>(GetStatus(i, k));
            }
        }
    }
    return VictoryStatus::Continue;
}

VictoryStatus tlCF::Board::TestCollumns() const {
    //test all collummns
    for (unsigned int i = 0; i < collumn_count; ++i) {
        for (unsigned int k = 0; k < row_count - 4; ++k) {
            if (GetStatus(k, i) != empty &&
                    GetStatus(k, i) == GetStatus(k + 1, i) &&
                    GetStatus(k, i) == GetStatus(k + 2, i) &&
                    GetStatus(k, i) == GetStatus(k + 3, i)) {
                return static_cast<VictoryStatus>(GetStatus(k, i));
            }
        }
    }

    return VictoryStatus::Continue;
}

tlCF::Board::Board() {
    Clear();
}

BoardFieldStatus Board::GetStatus(const uint32_t row, const uint32_t collumn) const {
    Expects(row < row_count);
    Expects(collumn < collumn_count);
    auto position = CalculateFieldPosition(row, collumn);
    return GetStatus(position);
}

bool tlCF::Board::ThrowIn(const uint32_t collumn, const BoardFieldStatus color) {
    Expects(collumn < collumn_count);
    Expects(color == red || color == yellow);

    bool result = CanThrowIn(collumn);
    //check upwards through all rows for an empty field
    for (unsigned int i = 0; i < row_count; ++i) {
        auto pos = CalculateFieldPosition(i, collumn);
        if (GetStatus(pos) == empty) {
            WritePosition(pos, color);
            break;
        }
    }

    Ensures(!result || ([&]() {
        auto c = empty;
        for (int i = static_cast<int>(row_count) - 1; i >= 0; --i) {
            c = this->GetStatus(i, collumn);
            if (c != empty) {
                break;
            }
        }
        return c;
    }() == color));
    return result;
}

bool tlCF::Board::CanThrowIn(const uint32_t collumn) const {
    Expects(collumn < collumn_count);
    //check topmost field
    return GetStatus(row_count-1, collumn)==empty;
}

void tlCF::Board::Clear() {
    std::fill(std::begin(data_), std::end(data_), 0);
}

VictoryStatus tlCF::Board::Test() const {
    auto rows = TestRows();
    if (rows != VictoryStatus::Continue) return rows;
    auto collumns = TestCollumns();
    if (collumns != VictoryStatus::Continue) return collumns;
    bool collumnsFull = true;
    for (int i = 0; i < collumn_count; ++i) {
        collumnsFull = collumnsFull && (!CanThrowIn(i)); //collumns full will get false if CanThrowIn is true for any collumn
    }
    if (collumnsFull) {
        return VictoryStatus::Draw;
    }
    return VictoryStatus::Continue;
}
