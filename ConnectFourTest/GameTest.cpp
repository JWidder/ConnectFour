#include "catch.hpp"
#include "ConnectFour.hpp"
#include <future>

#include "gsl_assert.h"

class CollumnPlayer : tlCF::Player {
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
    std::function<void(int)> callback_;
};