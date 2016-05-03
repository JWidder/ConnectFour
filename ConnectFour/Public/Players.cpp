#include "Players.hpp"

/* Random Player*/

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

/* MonteCarlo_ST*/

std::future<unsigned char> tlCF::MonteCarlo_ST::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
    return std::future<unsigned char>();
}

std::string tlCF::MonteCarlo_ST::GetName_Impl() const {
    return "MonteCarlo_ST";
}
