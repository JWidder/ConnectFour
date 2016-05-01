#include "catch.hpp"
#include "ConnectFour.hpp"
#include <future>

#include "gsl_assert.h"

class CollumnPlayer : public tlCF::Player {
  public:
    CollumnPlayer(unsigned char startCollumn) : collumn_(startCollumn) {
        Expects(startCollumn < 7);
    }
    // Inherited via Player
  private:

    virtual std::future<unsigned char> Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board, unsigned int timelimit) override {
        auto result = collumn_;
        collumn_ = (collumn_ + 1) % 7;
        Ensures(result < 7);
        std::promise<unsigned char> promise;
        promise.set_value(result);
        return promise.get_future();
    }

    virtual std::string GetName_Impl() const override {
        return "CollumnPlayer";
    }

    unsigned char collumn_;
};

TEST_CASE("Result is not 'continue'", "[game]") {
    std::function<tlCF::Player*()> red = []() {
        return new CollumnPlayer(0);
    };
    std::function<tlCF::Player*()> yellow = []() {
        return new CollumnPlayer(4);
    };
    tlCF::Game game(red, yellow);
    auto result = game.PlayGame();
    CHECK(result.result == tlCF::VictoryStatus::VictoryRed);
}

TEST_CASE("Performance Test - Random Player", "[.][performance][game]") {
    std::function<tlCF::Player*()> player = []() {
        return new tlCF::RandomPlayer();
    };
    tlCF::Game game(player, player);
    for (int i = 0; i < 10000; ++i) {
        game.Reset(false);
        auto result = game.PlayGame();
        CHECK(result.result != tlCF::VictoryStatus::Continue);
    }
}