#ifndef _UTILS_NINTACO_EVENT_HPP
#define _UTILS_NINTACO_EVENT_HPP

#include <cassert>

#include <memory>

#include <vector>
#include <unordered_map>

#include <nintaco/nintaco.hpp>

#include <SFML/Graphics.hpp>
#include <sfev/sfevmngr.hpp>
#include <sfev/kbmap.hpp>

#include "env/conf.hpp"

namespace nintaco
{
    class Event
    {
        private:
            std::unique_ptr<sf::RenderWindow> window;
            std::unique_ptr<sfev::EventManager> ev_manager;

            const std::vector<CONF::Action>& actions = CONF::ACTIONS;

            const std::unordered_map<CONF::Action, sf::Keyboard::Key> ev_key = {
                {CONF::Action::A, sfev::kbmap.at(CONF::KEY_A)},
                {CONF::Action::B, sfev::kbmap.at(CONF::KEY_B)},
                {CONF::Action::UP, sfev::kbmap.at(CONF::KEY_UP)},
                {CONF::Action::DOWN, sfev::kbmap.at(CONF::KEY_DOWN)},
                {CONF::Action::LEFT, sfev::kbmap.at(CONF::KEY_LEFT)},
                {CONF::Action::RIGHT, sfev::kbmap.at(CONF::KEY_RIGHT)},
                {CONF::Action::START, sfev::kbmap.at(CONF::KEY_START)},
                {CONF::Action::SELECT, sfev::kbmap.at(CONF::KEY_SELECT)}
            };

            std::unordered_map<CONF::Action, bool> ev_state = {
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
            Event() = default;

        public:
            void init(bool on);
            bool on() const;
            bool open() const;
            void process() const;

            void ev_setup();
            void get_action(std::vector<float>& act) const;

            const sfev::EventManager& get_ev_manager() const;

        public:
            Event(const Event &other) = delete;
            Event operator=(const Event &other) = delete;

        public:
            static Event &EVENT()
            {
                static Event singleton;
                return singleton;
            }
    };
}

#endif