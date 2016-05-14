#include "ConnectFour.hpp"
#include "gsl_assert.h"
#include <algorithm>

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcountll __popcnt64
#endif

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

VictoryStatus tlCF::Board::TestDiagonals() const {
    for (unsigned int i = 0; i < collumn_count - 4; ++i) {
        for (unsigned int k = 0; k < row_count - 4; ++k) {
            if (GetStatus(k, i) != empty &&
                    GetStatus(k, i) == GetStatus(k + 1, i + 1) &&
                    GetStatus(k, i) == GetStatus(k + 2, i + 2) &&
                    GetStatus(k, i) == GetStatus(k + 3, i + 3)) {
                return static_cast<VictoryStatus>(GetStatus(k, i));
            }
            if (GetStatus(i, k + 3) != empty &&
                    GetStatus(i, k + 3) == GetStatus(i + 1, k + 2) &&
                    GetStatus(i, k + 3) == GetStatus(i + 2, k + 1) &&
                    GetStatus(i, k + 3) == GetStatus(i + 3, k)) {
                return static_cast<VictoryStatus>(GetStatus(i, k + 3));
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
    auto diag = TestDiagonals();
    if (diag != VictoryStatus::Continue) return diag;
    bool collumnsFull = true;
    for (int i = 0; i < collumn_count; ++i) {
        collumnsFull = collumnsFull && (!CanThrowIn(i)); //collumns full will get false if CanThrowIn is true for any collumn
    }
    if (collumnsFull) {
        return VictoryStatus::Draw;
    }
    return VictoryStatus::Continue;
}

tlCF::BitBoard::BitBoard(uint64_t yellow, uint64_t red) {
    Clear();
    data_[0] = yellow;
    data_[1] = red;
}

tlCF::BitBoard::BitBoard(const BitBoard & b) {
    data_[0] = b.data_[0];
    data_[1] = b.data_[1];
}

BitBoard & tlCF::BitBoard::operator=(const BitBoard & b) {
    data_[0] = b.data_[0];
    data_[1] = b.data_[1];
    return *this;
}

BoardFieldStatus tlCF::BitBoard::GetStatus(const uint32_t row, const uint32_t collumn) const {
    auto shiftValue = (row + collumn*(row_count + 1));
    auto bitMask = 1ull << shiftValue;
    auto result = ((data_[IndexYellow] & bitMask) >> shiftValue) + 2 * ((data_[IndexRed] & bitMask) >> shiftValue);
    return static_cast<BoardFieldStatus>(result);
}

bool tlCF::BitBoard::ThrowIn(const uint32_t collumn, const BoardFieldStatus color) {
    Expects(color == yellow || color == red);
    if (!CanThrowIn(collumn)) return false;
    auto bitMask = 0b111111ull << (collumn*(row_count + 1)); //mask out a collumn
    auto field = (data_[0] | data_[1])& bitMask;
    //since we masked out all other parts of the field, only the used slots in our collumn remain and we can count them
    auto usedFields = __builtin_popcountll(field);
    data_[color-1] |= 1ull << (usedFields + collumn*(row_count + 1));
    return true;
}

bool tlCF::BitBoard::CanThrowIn(const uint32_t collumn) const {
    auto fillStatus = data_[IndexYellow] | data_[IndexRed];
    auto mask = 0b100000ull << collumn*(row_count + 1); //check top-most field
    return (fillStatus & mask) == 0;
}

void tlCF::BitBoard::Clear() {
    std::fill(std::begin(data_), std::end(data_), 0);
}

VictoryStatus tlCF::BitBoard::Test() const {
    //test is done via clever shifting.
    //first a shift by 1 clears out the first element
    //and clears out something in between if there's
    //a hole
    //then a shift by 2 checks if there are still items
    //when the result is not 0, there was a match
    //this can be done in parallel for all possible
    //solutions in one of the direction
    //(horizontal, vertical, diag1, diag2)
    auto fillStatus = data_[IndexYellow] | data_[IndexRed];
    auto mask = 0b100000ull << 0 * (row_count + 1) |
                0b100000ull << 1 * (row_count + 1) |
                0b100000ull << 2 * (row_count + 1) |
                0b100000ull << 3 * (row_count + 1) |
                0b100000ull << 4 * (row_count + 1) |
                0b100000ull << 5 * (row_count + 1) |
                0b100000ull << 6 * (row_count + 1);
    auto bits = fillStatus & mask;
    if (__builtin_popcountll(bits) == 7) return VictoryStatus::Draw;
    else if (hasWon(yellow)) return VictoryStatus::VictoryYellow;
    else if (hasWon(red)) return VictoryStatus::VictoryRed;
    else return VictoryStatus::Continue;
}

bool tlCF::BitBoard::hasWon(BoardFieldStatus color) const {
    Expects(color == red || color == yellow);
    auto data = data_[color - 1];
    auto vert = data & (data >> 1);
    auto v_result = vert & (vert >> 2);
    auto hori = data & (data >> (row_count + 1));
    auto h_result = hori & (hori >> (2 * (row_count + 1)));
    //shift one less than the actual height
    auto diag1 = data & (data >> row_count);
    auto d1_result = diag1 & (diag1 >> (2 * row_count));
    //shift one more than the actual height
    auto diag2 = data & (data >> (row_count + 2));
    auto d2_result = diag2 & (diag2 >> (2 * (row_count + 2)));
    return (v_result | h_result | d1_result | d2_result)!=0;
}

std::future<unsigned char> tlCF::Player::Play(BoardFieldStatus color, const BitBoard& board) {
    Expects(color == yellow || color == red);
    return Play_Impl(color, board);
}

void tlCF::Player::Reset() {
    Reset_Impl();
}

std::string tlCF::Player::GetName() const {
    return GetName_Impl();
}

std::string tlCF::Player::GetLogEntry() const {
    return GetLogEntry_Impl();
}

tlCF::Game::Game(Player* yellow, Player* red) {
    Expects(yellow != nullptr);
    Expects(red != nullptr);
    players_[0] = yellow;
    players_[1] = red;
    init();
}

void tlCF::Game::init() {
    std::fill(std::begin(moves_), std::end(moves_), empty);
    board_.Clear();
    players_[0]->Reset();
    players_[1]->Reset();
    terminate_ = false;
}

void tlCF::Game::Reset(bool swapPlayer) {
    if (swapPlayer) {
        std::swap(players_[0], players_[1]);
    }
    init();
}

tlCF::GameResult::GameResult(const tlCF::GameResult& rhs)
    : red(rhs.red)
    , yellow(rhs.yellow)
    , result(rhs.result) {
    std::copy(std::begin(rhs.moves), std::end(rhs.moves), std::begin(moves));
}

GameResult & tlCF::GameResult::operator=(const GameResult & rhs) {
    red = rhs.red;
    yellow = rhs.yellow;
    result = rhs.result;
    std::copy(std::begin(rhs.moves), std::end(rhs.moves), std::begin(moves));
    return *this;
}

GameResult tlCF::Game::PlayGame() {
    unsigned int playerIndex = 0;
    unsigned int moveIndex = 0;
    while (board_.Test() == VictoryStatus::Continue) {
        auto future_move = players_[playerIndex]->Play(static_cast<BoardFieldStatus>(playerIndex+1),board_);
        while (future_move.wait_for(std::chrono::seconds(1)) != std::future_status::ready) {
            if (terminate_) return GameResult();
        }
        auto move = future_move.get();
        moves_[moveIndex] = move;

        if (!board_.CanThrowIn(move)) break; //break off due to illegal move
        else (board_.ThrowIn(move, static_cast<BoardFieldStatus>(playerIndex + 1)));

        playerIndex = (playerIndex + 1) % 2;
        moveIndex += 1;

        if (observer_) observer_(board_);
        std::this_thread::sleep_for(std::chrono::microseconds(20));
    }
    playerIndex = (playerIndex + 1) % 2; //adjust index back to the one that moved last
    GameResult result;
    result.yellow = players_[0]->GetName();
    result.red = players_[1]->GetName();
    result.result = (board_.Test() == VictoryStatus::Continue) ? static_cast<VictoryStatus>(playerIndex + 1) : board_.Test();
    std::copy(std::begin(moves_), std::end(moves_),std::begin(result.moves));
    Ensures(result.result != VictoryStatus::Continue);
    return result;
}

void tlCF::Game::RegisterObserver(std::function<void(tlCF::BitBoard)> observer) {
    observer_ = observer;
}

std::string tlCF::Game::GetRed() const {
    return players_[1]->GetName();
}

std::string tlCF::Game::GetYellow() const {
    return players_[0]->GetName();
}
