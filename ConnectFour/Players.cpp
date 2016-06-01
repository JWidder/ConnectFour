#include "Players.hpp"

#include "gsl_assert.h"
#include "ConnectFour.hpp"

#include <sstream>
#include <thread>
#include <chrono>

tlCF::RandomPlayer::RandomPlayer()
    : engine_(dev_()) {

}

std::future<unsigned char> tlCF::RandomPlayer::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    std::uniform_int_distribution<> dist(0, 6);
    std::promise<unsigned char> promise;
    promise.set_value(dist(engine_));
    return promise.get_future();
}

std::string tlCF::RandomPlayer::GetName_Impl() const {
    return "RandomPlayer";
}

std::string tlCF::RandomPlayer::GetInitialState_Impl() const {
    std::stringstream state;
    state << engine_;
    return state.str();
}

struct MCResult {
    uint32_t score;
    uint32_t count;

    MCResult() : score(0), count(0) {}
};

//there seems to be a flaw - the following sequence leads to an unnecessary loss:
//r3, y3, r4, y2, r6, y5, r5, y3, r3, y5, r5, y4, r4 -> red wins
//and this sequence is reproducible!

std::future<unsigned char> tlCF::MonteCarlo_SingleThreaded::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    if (thread_ && thread_->joinable()) {
        thread_->join();
    }    
    result_ = std::promise<unsigned char>();
    auto retval = result_.get_future();
    thread_ = std::make_unique<std::thread>([=, &result = result_]() {
        MCResult data[7];
        auto startposition = board;
        const int batch_size = 1000;
        const int draw_score = 1;
        const int victory_score = 2;
        
        std::uniform_int_distribution<> dist(0, 6);
        //get "now"
        auto now = std::chrono::high_resolution_clock::now();

        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count() < timelimit_in_ms_) {
            //start a cycle
            for (int slot = 0; slot < 7; ++slot) {
                if (startposition.CanThrowIn(slot) != true) {
                    data[slot].count += batch_size;
                    continue;
                }
                for (int i = 0; i < batch_size; ++i) {
                    auto simulation_board = startposition;
                    auto stone = color;
                    simulation_board.ThrowIn(slot, stone);
                    //simulation loop
                    VictoryStatus simulation_result;
                    int moveCount = 0;
                    while ((simulation_result = simulation_board.Test()) == tlCF::VictoryStatus::Continue) {
                        stone = stone == red ? yellow : red;
                        auto selected_collumn = dist(engine_);
                        while (!simulation_board.CanThrowIn(selected_collumn)) {
                            selected_collumn = dist(engine_);
                        }
                        simulation_board.ThrowIn(selected_collumn, stone);
                        moveCount += 1;
                    }

                    if (simulation_result == VictoryStatus::Draw) {
                        data[slot].score += (7*6-moveCount)*draw_score;
                    }
                    else if (static_cast<int>(simulation_result) == color) {
                        data[slot].score += (7 * 6 - moveCount)*victory_score;
                    }
                }
                data[slot].count += batch_size;
            }
        }
        //find index with max count
        uint32_t max = data[0].score;
        unsigned char index = 0;
        for (int i = 1; i < 7; ++i) {
            if (max < data[i].score) {
                max = data[i].score;
                index = i;
            }
        }
        result.set_value(index);
    });
    return retval;
}

std::string tlCF::MonteCarlo_SingleThreaded::GetName_Impl() const {
    std::stringstream result;
    result << "MonteCarlo_SingleThreaded_" << timelimit_in_ms_;
    return result.str();
}

std::string tlCF::MonteCarlo_SingleThreaded::GetInitialState_Impl() const {
    std::stringstream state;
    state << timelimit_in_ms_<<",";
    state << engine_;
    return state.str();
}

std::future<unsigned char> tlCF::MCST_UB1::Play_Impl(BoardFieldStatus color, const BitBoard & board)
{
    return std::future<unsigned char>();
}

std::string tlCF::MCST_UB1::GetName_Impl() const
{
    std::stringstream result;
    result << "MCST_UB1_" << timelimit_in_ms_;
    return result.str();
}

std::string tlCF::MCST_UB1::GetInitialState_Impl() const {
    std::stringstream state;
    state << timelimit_in_ms_ << ",";
    state << engine_;
    return state.str();
}
