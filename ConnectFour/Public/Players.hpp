#pragma once
#include "ConnectFour.hpp"

#include <random>
#include <thread>
#include <memory>
#include <cmath>

#include <foonathan/memory/memory_pool.hpp>
#include <foonathan/memory/smart_ptr.hpp>

namespace tlCF {

    class RandomPlayer final : public Player {
      public:
        RandomPlayer();
      private:

        // Inherited via Player
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
        virtual std::string GetName_Impl() const override final;
        std::string GetInitialState_Impl() const override final;

        std::random_device dev_;
        std::mt19937 engine_;
    };

    class MonteCarlo_SingleThreaded final : public Player {

      public:
        MonteCarlo_SingleThreaded(unsigned int timelimit = 2000)
        : timelimit_in_ms_(timelimit)
        , engine_(dev_()) {
        }
        ~MonteCarlo_SingleThreaded() {
            if (thread_ && thread_->joinable()) {
                thread_->join();
            }
        }
      private:
        // Inherited via Player
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
        virtual std::string GetName_Impl() const override final;
        virtual std::string GetInitialState_Impl() const override final;

        //member
        unsigned int timelimit_in_ms_;
        std::random_device dev_;
        std::mt19937 engine_;
        std::promise<unsigned char> result_;
        std::unique_ptr<std::thread> thread_;
    };

    namespace detail {
        struct MonteCarloTreeNode {

        };
    }

    class MCST_UB1 : public Player {
        const unsigned int MinPlayoutsBeforeExpansion = 4;
        const double ExplorationConstant = std::sqrt(2);
        static const size_t TreeSize = 4 * 1024 * 1024 * 1024;
    public:
        MCST_UB1(unsigned int timelimit = 2000)
            : timelimit_in_ms_(timelimit)
            , engine_(dev_())
            , memory_pool_(sizeof(detail::MonteCarloTreeNode)+16, TreeSize){
        }
        ~MCST_UB1() {
            if (thread_ && thread_->joinable()) {
                thread_->join();
            }
        }
    private:
        // Inherited via Player
        virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
        virtual std::string GetName_Impl() const override final;
        virtual std::string GetInitialState_Impl() const override final;

        //functions
        bool Playout(tlCF::BitBoard board) const; //single playout. Returns true for a win.

    private:
        //member
        unsigned int timelimit_in_ms_;
        std::random_device dev_;
        std::mt19937 engine_;
        std::promise<unsigned char> result_;
        std::unique_ptr<std::thread> thread_;
        foonathan::memory::memory_pool<> memory_pool_;
        std::shared_ptr<detail::MonteCarloTreeNode> root_;
    };

}