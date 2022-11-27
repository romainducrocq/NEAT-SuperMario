#ifndef _UTILS_NINTACO_ACTION_HPP
#define _UTILS_NINTACO_ACTION_HPP

#include <cassert>
#include <limits>

#include <memory>

#include <array>
#include <vector>

#include <nintaco/nintaco.hpp>

#include "utils/nintaco/api.hpp"

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
            struct Noop
            {
                std::unique_ptr<size_t> act1;
                std::unique_ptr<size_t> act2;

                inline bool is() const
                {
                    return this->act1.get() && this->act2.get();
                }
            };

        private:
            std::array<nintaco::Action::Noop, 2> noops;

            const std::vector<CONF::Action>& actions = CONF::ACTIONS;

        private:
            Action() = default;

        public:
            void init();

            void act_func(std::vector<float>& act) const;

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