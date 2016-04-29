#pragma once

#include <cstdint>
#include <memory>
#include <functional>
#include <future>

namespace tlCF {

    enum BoardFieldStatus : uint8_t { empty = 0, yellow = 1, red = 2};
    enum class VictoryStatus { Continue, VictoryYellow = yellow, VictoryRed = red, Draw};

    uint32_t GetMask(uint32_t bitPosition);

    //42 fields with 2 bits of status = 84 bits ~ 11bytes
    //one added byte to stay at 32bit boundary
    //organized row - collumn
    class Board {
      public:
        const static uint32_t row_count = 6;
        const static uint32_t collumn_count = 7;

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

        VictoryStatus TestRows() const;
        VictoryStatus TestCollumns() const;
        VictoryStatus TestDiagonals() const;

        uint32_t data_[3];
    };

    class BitBoard {
      public:
        const static uint32_t row_count = 6;
        const static uint32_t collumn_count = 7;

        BitBoard();

        BoardFieldStatus GetStatus(const uint32_t row, const uint32_t collumn) const;
        bool ThrowIn(const uint32_t collumn, const BoardFieldStatus color);
        bool CanThrowIn(const uint32_t collumn) const;
        void Clear();

        VictoryStatus Test() const;
      private:

        bool hasWon(BoardFieldStatus color) const;

        const unsigned int IndexYellow = 0;
        const unsigned int IndexRed = 1;
        //each element of data_ contains bit-coded whether a certain color is set or not
        //Assigned bits:
        //top row is free
        //5 12 19 26 33 40 47
        //4 11 18 25 32 39 46
        //3 10 17 24 31 38 55
        //2  9 16 23 30 37 44
        //1  8 15 22 29 36 43
        //0  7 14 21 28 35 42
        //the skipped bits (additional bits) for the top row are intentional
        //they are required for the test-algorithms based on shifts
        //to avoid matches due to overflow
        uint64_t data_[2];
    };

    class Player {
      public:
        std::future<unsigned char> Play(BoardFieldStatus color, const BitBoard& board, unsigned int timelimit);

        std::string GetName() const;

      protected:
        virtual void SetCallback_Impl(std::function<void(int)> callback) = 0;
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard& board, unsigned int timelimit) = 0;
        virtual std::string GetName_Impl() const = 0;
    };

    struct GameResult {
        std::string red;
        std::string yellow;
        VictoryStatus result;
        unsigned char moves[42];
    };

    class Game {
      public:
        Game(std::function<Player*()> yellow, std::function<Player*()> red);

        void Reset(bool swapPlayer);

        GameResult PlayGame();

      private:
        void init();

        std::function<Player*()> yellow_;
        std::function<Player*()> red_;

        std::unique_ptr<Player> players_[2];
        BitBoard board_;
        unsigned char moves_[42]; //maximum 42 moves
    };

}