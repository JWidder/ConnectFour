#include "catch.hpp"
#include "ConnectFour.hpp"
#include "Players.hpp"
#include <future>

#include "gsl_assert.h"

class CollumnPlayer : public tlCF::Player {
  public:
    CollumnPlayer(unsigned char startCollumn) : collumn_(startCollumn) {
        Expects(startCollumn < 7);
    }
    // Inherited via Player
  private:

    virtual std::future<unsigned char> Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board) override {
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

    virtual std::string GetInitialState_Impl() const override {
        return "";
    }

    unsigned char collumn_;
};

TEST_CASE("Result is not 'continue'", "[game]") {
    auto yellow = std::make_unique<CollumnPlayer>(0);
    auto red = std::make_unique<CollumnPlayer>(4);
    tlCF::Game game(yellow.get(), red.get());
    auto result = game.PlayGame();
    CHECK(result.result == tlCF::VictoryStatus::VictoryYellow);
}

TEST_CASE("Performance Test - Random Player", "[.][performance][game]") {
    auto random = std::make_unique<tlCF::RandomPlayer>();
    auto random2 = std::make_unique<tlCF::RandomPlayer>();

    tlCF::Game game(random.get(), random2.get());
    for (int i = 0; i < 10000; ++i) {
        game.Reset(false);
        auto result = game.PlayGame();
        CHECK(result.result != tlCF::VictoryStatus::Continue);
    }
}