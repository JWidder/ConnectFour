#pragma once

#include <cstdint>

namespace tlCF {

    enum BoardFieldStatus : uint8_t { empty = 0, yellow = 1, red = 2};
    enum class VictoryStatus { Continue, VictoryRed, VictoryYellow, Draw};

    uint32_t GetMask(uint32_t bitPosition);

    //42 fields with 2 bits of status = 84 bits ~ 11bytes
    //one added byte to stay at 32bit boundary
    //organized row - collumn
    class Board {
      public:
        const static uint32_t row_size = 6;
        const static uint32_t collumn_size = 7;

        Board();

        BoardFieldStatus GetStatus(const uint32_t row, const uint32_t collumn) const;
        bool ThrowIn(const uint32_t collumn, const BoardFieldStatus color);
        bool CanThrowIn(const uint32_t collumn) const;
        void Clear();
        VictoryStatus Test() const;

      private:
        struct FieldPosition {
            uint32_t array_index;
            uint32_t position;
        };

        FieldPosition CalculateFieldPosition(const uint32_t row, const uint32_t collumn) const;
        BoardFieldStatus GetStatus(FieldPosition position) const;
        void WritePosition(FieldPosition pos, BoardFieldStatus color);

        uint32_t data_[3];
        BoardFieldStatus lastColor_;
    };

}