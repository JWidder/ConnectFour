#pragma once
#include "ConnectFour.hpp"

#include <random>
#include <thread>
#include <memory>

namespace tlCF {

    class RandomPlayer : public Player {
      public:
        RandomPlayer();
      private:

        // Inherited via Player
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
        virtual std::string GetName_Impl() const override final;

        std::random_device dev_;
        std::mt19937 engine_;
    };

    class MonteCarlo_ST : public Player {

      public:
        MonteCarlo_ST(unsigned int timelimit = 2000) : timelimit_in_ms_(timelimit) {}
        ~MonteCarlo_ST() {
            if (thread_ && thread_->joinable()) {
                thread_->join();
            }
        }
      private:
        // Inherited via Player
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
        virtual std::string GetName_Impl() const override final;

        //member
        unsigned int timelimit_in_ms_;
        std::promise<unsigned char> result_;
        std::unique_ptr<std::thread> thread_;
    };

}