#ifndef _UTILS_NINTACO_STATE_HPP
#define _UTILS_NINTACO_STATE_HPP

#include <chrono>

#include <thread>

#include <nintaco/nintaco.hpp>

#include "utils/nintaco/api.hpp"

#include "env/conf.hpp"

namespace nintaco
{
    class State
    {
        private:
            std::string sav = "../../res/sav/" + CONF::ROM + "_" + CONF::SAV + ".save";

            bool ini = true;

        private:
            State() = default;

        private:
            void quick_save() const;
            void quick_load() const;

        public:
            void init();

            void reset();
            void load(); // TODO -> private if reset ok

        public:
            State(const State &other) = delete;
            State operator=(const State &other) = delete;

            static State &STATE()
            {
                static State singleton;
                return singleton;
            }
    };
}

#endif