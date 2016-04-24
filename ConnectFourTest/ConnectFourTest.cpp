#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gsl_assert.h"

#include "ConnectFour.hpp"

using namespace tlCF;



TEST_CASE("default board is empty", "[board]") {
    Board b;
    for (uint32_t i = 0; i < Board::collumn_count; ++i) {
        for (uint32_t k = 0; k < Board::row_count; ++k) {
            CHECK(b.GetStatus(k, i) == empty);
        }
    }
}

BoardFieldStatus Flip(BoardFieldStatus f) {
    Expects(f == red || f == yellow);
    BoardFieldStatus result = f;
    if (f == red) result = yellow;
    else if (f == yellow) result = red;
    Ensures(result != f);
    Ensures(result == red || result == yellow);
    return result;
}

template <typename Board_t>
void throwinTest() {
    Board_t b;
    BoardFieldStatus color = red;
    for (uint32_t i = 0; i < Board_t::collumn_count; ++i) {
        for (uint32_t k = 0; k < Board_t::row_count; ++k) {
            INFO("k: " << k << " i:" << i);
            CHECK(b.GetStatus(k, i) == empty);
            CHECK(b.ThrowIn(i, color) == true);
            CHECK(b.GetStatus(k, i) == color);
            color = Flip(color);
        }
    }
}

TEST_CASE("throwing in a color works", "[board]") {
    throwinTest<Board>();
    throwinTest<BitBoard>();
}

template <typename Board_t>
void clearBoardTest() {
    Board_t b;
    BoardFieldStatus color = red;
    b.ThrowIn(4, color);
    CHECK(b.GetStatus(0, 4) == color);
    b.Clear();
    CHECK(b.GetStatus(0, 4) == empty);
}

TEST_CASE("clearing the board works", "[board]") {
    clearBoardTest<Board>();
    clearBoardTest<BitBoard>();
}

template <typename Board_t>
void testContinue() {
    Board_t b;
    CHECK(b.Test() == VictoryStatus::Continue);
}

TEST_CASE("Testing the empty board means continue", "[board]") {
    testContinue<Board>();
    testContinue<BitBoard>();
}

template <typename Board_t>
void testDraw() {
    Board_t b;
    //fill board
    std::vector<std::vector<int>> data = { { 1,1,1,2,1,1 },
        { 1,1,1,2,1,1 },
        { 1,1,2,2,2,1 },
        { 2,2,2,1,2,2 },
        { 1,1,2,2,2,1 },
        { 1,1,1,2,1,1 },
        { 1,1,1,2,1,1 }
    };
    uint32_t collumn = 0;
    for (const auto& i : data) {
        for (const auto& k : i) {
            b.ThrowIn(collumn, static_cast<BoardFieldStatus>(k));
        }
        collumn += 1;
    }
    CHECK(b.Test() == VictoryStatus::Draw);
}

TEST_CASE("Full Board means draw", "[board]") {
    testDraw<Board>();
    testDraw<BitBoard>();
}

template <typename Board_t>
void testRow() {
    Board_t b;
    for (unsigned int i = 0; i < 4; ++i) {
        b.ThrowIn(i, red);
    }
    CHECK(b.Test() == VictoryStatus::VictoryRed);
}

TEST_CASE("4 in a row win") {
    testRow<Board>();
    testRow<BitBoard>();
}

template <typename Board_t>
void testCollumn() {
    Board_t b;
    b.ThrowIn(5, red);
    for (unsigned int i = 0; i < 4; ++i) {
        b.ThrowIn(5, yellow);
    }
    CHECK(b.Test() == VictoryStatus::VictoryYellow);
}

TEST_CASE("4 in a collumn win") {
    testCollumn<Board>();
    testCollumn<BitBoard>();
}

template <typename Board_t>
void testDiagUp() {
    Board_t b;
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < i; ++k) {
            b.ThrowIn(i + 1, yellow);
        }
        b.ThrowIn(i + 1, red);
    }
    CHECK(b.Test() == VictoryStatus::VictoryRed);
}

TEST_CASE("4 in a upwards diagonal win") {
    testDiagUp<Board>();
    testDiagUp<BitBoard>();
}

template <typename Board_t>
void testDiagDown() {
    Board_t b;
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < 3 - i; ++k) {
            b.ThrowIn(i + 1, red);
        }
        b.ThrowIn(i + 1, yellow);
    }
    CHECK(b.Test() == VictoryStatus::VictoryYellow);
}

TEST_CASE("4 in a downwards diagonal win") {
    testDiagDown<Board>();
    testDiagDown<BitBoard>();
}
