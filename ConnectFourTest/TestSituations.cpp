#include "catch.hpp"
#include "Players.hpp"
#include "ConnectFour.hpp"

TEST_CASE("double threat test","[montecarlo_singlethreaded]") {
    tlCF::BitBoard board(171811291136ull, 4741931204608ull);
    tlCF::MonteCarlo_SingleThreaded player;
    auto result = player.Play(tlCF::yellow, board);
    auto collumn = result.get();
    CHECK(collumn != 4);
}