#ifndef _UTILS_NINTACO_ACTION_HPP
#define _UTILS_NINTACO_ACTION_HPP

#include <cassert>
#include <limits>

#include <vector>
#include <unordered_map>

#include <nintaco/nintaco.hpp>

#include "env/conf.hpp"

namespace nintaco
{
    class Action
    {
        private:
            struct Output
            {
                static inline bool activate(float z)
                {
                    return z > std::numeric_limits<float>::min();
                }
            };

        private:
            const std::vector<CONF::Action>& actions = CONF::ACTIONS;

            std::unordered_map<CONF::Action, bool> act_state = {
                {CONF::Action::A, false},
                {CONF::Action::B, false},
                {CONF::Action::UP, false},
                {CONF::Action::DOWN, false},
                {CONF::Action::LEFT, false},
                {CONF::Action::RIGHT, false},
                {CONF::Action::START, false},
                {CONF::Action::SELECT, false}
            };

        private:
            Action() = default;

        public:
            Action(const Action &other) = delete;
            Action operator=(const Action &other) = delete;

        public:
            static Action &ACTION()
            {
                static Action singleton;
                return singleton;
            }
    };
}

#endif