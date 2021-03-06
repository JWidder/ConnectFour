#include "Players.hpp"

#include "gsl_assert.h"
#include "ConnectFour.hpp"

#include <sstream>
#include <thread>
#include <chrono>
#include <cmath>

tlCF::RandomPlayer::RandomPlayer()
    : engine_(dev_()) {

}

std::future<unsigned char> tlCF::RandomPlayer::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    std::vector<unsigned char> eligible_slots;
    //detect valid slots
    for (int slot = 0; slot < 7; ++slot) {
        if (board.CanThrowIn(slot) == true) {
            eligible_slots.push_back(slot);
        }
    }
    //pick a random slot from the list of eligible_slots
    //if no eligible_slot, take 0
    std::promise<unsigned char> promise;
    if (eligible_slots.empty()) {
        promise.set_value(0);
    }
    else {
        std::uniform_int_distribution<> dist(0, static_cast<int>(eligible_slots.size() - 1));
        promise.set_value(eligible_slots[dist(engine_)]);
    }
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

void MonteCarlo_SingleThreaded_TimeStrategy(tlCF::BoardFieldStatus color, tlCF::BitBoard board, std::promise<unsigned char>& result, std::mt19937& engine, unsigned int timelimit_in_ms) {
    using namespace tlCF;
    MCResult data[7];
    auto startposition = board;
    const int batch_size = 1000;
    const int draw_score = 1;
    const int victory_score = 2;

    std::uniform_int_distribution<> dist(0, 6);
    //get "now"
    auto now = std::chrono::high_resolution_clock::now();

    std::vector<unsigned char> eligible_slots;
    //detect valid slots
    for (int slot = 0; slot < 7; ++slot) {
        if (startposition.CanThrowIn(slot) == true) {
            eligible_slots.push_back(slot);
        }
    }
    if (eligible_slots.empty()) {
        result.set_value(0); //take any slot as no slot is valid
        return;
    }
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count() < timelimit_in_ms) {
        //start a cycle, simulating only valid slots
        for (auto slot : eligible_slots) {
            for (int i = 0; i < batch_size; ++i) {
                auto simulation_board = startposition;
                auto stone = color;
                simulation_board.ThrowIn(slot, stone);
                //simulation loop
                VictoryStatus simulation_result;
                int moveCount = 0;
                while ((simulation_result = simulation_board.Test()) == tlCF::VictoryStatus::Continue) {
                    stone = stone == red ? yellow : red;
                    auto selected_collumn = dist(engine);
                    while (!simulation_board.CanThrowIn(selected_collumn)) {
                        selected_collumn = dist(engine);
                    }
                    simulation_board.ThrowIn(selected_collumn, stone);
                    moveCount += 1;
                }

                if (simulation_result == VictoryStatus::Draw) {
                    data[slot].score += (7 * 6 - moveCount)*draw_score;
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
    for (auto i : eligible_slots) {
        if (max < data[i].score) {
            max = data[i].score;
            index = i;
        }
    }
    result.set_value(index);
}

void MonteCarlo_SingleThreaded_SimulationCountStrategy(tlCF::BoardFieldStatus color, tlCF::BitBoard board, std::promise<unsigned char>& result, std::mt19937& engine, unsigned int simulations_per_slot) {
    using namespace tlCF;
    MCResult data[7];
    auto startposition = board;
    const int draw_score = 1;
    const int victory_score = 2;

    std::uniform_int_distribution<> dist(0, 6);
    //get "now"
    auto now = std::chrono::high_resolution_clock::now();

    std::vector<unsigned char> eligible_slots;
    //detect valid slots
    for (int slot = 0; slot < 7; ++slot) {
        if (startposition.CanThrowIn(slot) == true) {
            eligible_slots.push_back(slot);
        }
    }
    if (eligible_slots.empty()) {
        result.set_value(0); //take any slot as no slot is valid
        return;
    }
    //start a cycle, simulating only valid slots
    for (auto slot : eligible_slots) {
        for (unsigned int i = 0; i < simulations_per_slot; ++i) {
            auto simulation_board = startposition;
            auto stone = color;
            simulation_board.ThrowIn(slot, stone);
            //simulation loop
            VictoryStatus simulation_result;
            int moveCount = 0;
            while ((simulation_result = simulation_board.Test()) == tlCF::VictoryStatus::Continue) {
                stone = stone == red ? yellow : red;
                auto selected_collumn = dist(engine);
                while (!simulation_board.CanThrowIn(selected_collumn)) {
                    selected_collumn = dist(engine);
                }
                simulation_board.ThrowIn(selected_collumn, stone);
                moveCount += 1;
            }

            if (simulation_result == VictoryStatus::Draw) {
                data[slot].score += (7 * 6 - moveCount)*draw_score;
            }
            else if (static_cast<int>(simulation_result) == color) {
                data[slot].score += (7 * 6 - moveCount)*victory_score;
            }
        }
        data[slot].count += simulations_per_slot;
    }
    //find index with max count
    uint32_t max = data[0].score;
    unsigned char index = 0;
    for (auto i : eligible_slots) {
        if (max < data[i].score) {
            max = data[i].score;
            index = i;
        }
    }
    result.set_value(index);
}


std::future<unsigned char> tlCF::MonteCarlo_SingleThreaded::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    if (thread_ && thread_->joinable()) {
        thread_->join();
    }
    result_ = std::promise<unsigned char>();
    auto retval = result_.get_future();
    if (strategy_ == MonteCarlo_SingleThreadedStrategy::Time) {
        thread_ = std::make_unique<std::thread>([=, &result = result_]() {
            MonteCarlo_SingleThreaded_TimeStrategy(color, board, result_, engine_, play_strength_);
        });
    }
    else {
        thread_ = std::make_unique<std::thread>([=, &result = result_]() {
            MonteCarlo_SingleThreaded_SimulationCountStrategy(color, board, result_, engine_, play_strength_);
        });
    }
    return      retval;
}

std::string tlCF::MonteCarlo_SingleThreaded::GetName_Impl() const {
    std::stringstream result;
    if (strategy_ == MonteCarlo_SingleThreadedStrategy::Time) {
        result << "MonteCarlo_SingleThreaded_Time_" << play_strength_;
    }
    else {
        result << "MonteCarlo_SingleThreaded_Count_" << play_strength_;
    }
    return result.str();
}

std::string tlCF::MonteCarlo_SingleThreaded::GetInitialState_Impl() const {
    std::stringstream state;
    state << play_strength_ <<",";
    state << engine_;
    return state.str();
}

std::future<unsigned char> tlCF::MCST_UB1::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    return std::future<unsigned char>();
}

std::string tlCF::MCST_UB1::GetName_Impl() const {
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
