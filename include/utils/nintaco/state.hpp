#ifndef _UTILS_NINTACO_STATE_HPP
#define _UTILS_NINTACO_STATE_HPP

#include <nintaco/nintaco.hpp>

#include "utils/nintaco/api.hpp"

#include "env/conf.hpp"

namespace nintaco
{
    class State
    {
        private:
            std::string sav = "../../res/sav/" + CONF::ROM + "_" + CONF::SAV + ".save";

        private:
            State() = default;

        public:
            void init();

            void load();

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