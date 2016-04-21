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
    Expects(row < row_size);
    Expects(collumn < collumn_size);
    auto field_index = collumn*row_size + row;
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
    lastColor_ = color;
    Ensures(lastColor_ = color);
}

tlCF::Board::Board()
    : lastColor_(empty) {
    Clear();
}

BoardFieldStatus Board::GetStatus(const uint32_t row, const uint32_t collumn) const {
    Expects(row < row_size);
    Expects(collumn < collumn_size);
    auto position = CalculateFieldPosition(row, collumn);
    return GetStatus(position);
}

bool tlCF::Board::ThrowIn(const uint32_t collumn, const BoardFieldStatus color) {
    Expects(collumn < collumn_size);
    Expects(color == red || color == yellow);

    bool result = CanThrowIn(collumn);
    for (unsigned int i = 0; i < row_size; ++i) {
        auto pos = CalculateFieldPosition(i, collumn);
        if (GetStatus(pos) == empty) {
            WritePosition(pos, color);
            break;
        }
    }

    Ensures(!result || ([&]() {
        auto c = empty;
        for (int i = static_cast<int>(row_size) - 1; i >= 0; --i) {
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
    Expects(collumn < collumn_size);
    return GetStatus(row_size-1, collumn)==empty;
}

void tlCF::Board::Clear() {
    std::fill(std::begin(data_), std::end(data_), 0);
}

VictoryStatus tlCF::Board::Test() const {
    bool collumnsFull = true;
    for (int i = 0; i < collumn_size; ++i) {
        collumnsFull = collumnsFull && (!CanThrowIn(i)); //collumns full will get false if CanThrowIn is true for any collumn
    }
    if (collumnsFull) {
        return VictoryStatus::Draw;
    }
    return VictoryStatus::Continue;
}
