#ifndef _UTILS_NINTACO_EVENT_HPP
#define _UTILS_NINTACO_EVENT_HPP

#include <cstdlib>

#include <thread>
#include <memory>

#include <array>
#include <vector>
#include <unordered_map>
#include <utility>

#include <nintaco/nintaco.hpp>

#include <SFML/Graphics.hpp>
#include <sfev/sfevmngr.hpp>
#include <sfev/sfmap.hpp>

#include "utils/nintaco/api.hpp"

#include "env/conf.hpp"

namespace nintaco
{
    class Event
    {
        private:
            bool wmctrl = true;

            bool on = CONF::KEYBOARD_SFML;
            bool gamepad = CONF::MODE == CONF::Mode::PLAY;

            std::unique_ptr<sf::RenderWindow> window;
            std::unique_ptr<sfev::EventManager> ev_manager;

            const std::vector<CONF::Action>& actions = CONF::ACTIONS;

            std::unordered_map<CONF::Action, std::pair<sf::Keyboard::Key, bool>> keys = {
                {CONF::Action::A, {sfev::kbmap.at(CONF::KEY_A), false}},
                {CONF::Action::B, {sfev::kbmap.at(CONF::KEY_B), false}},
                {CONF::Action::UP, {sfev::kbmap.at(CONF::KEY_UP), false}},
                {CONF::Action::DOWN, {sfev::kbmap.at(CONF::KEY_DOWN), false}},
                {CONF::Action::LEFT, {sfev::kbmap.at(CONF::KEY_LEFT), false}},
                {CONF::Action::RIGHT, {sfev::kbmap.at(CONF::KEY_RIGHT), false}},
                {CONF::Action::START, {sfev::kbmap.at(CONF::KEY_START), false}},
                {CONF::Action::SELECT, {sfev::kbmap.at(CONF::KEY_SELECT), false}}
            };

        private:
            bool is() const;

        private:
            Event() = default;

        public:
            void init();
            bool open() const;
            void process() const;
            void focus();

            void ev_setup();
            void get_action(std::array<float, CONF::OUTPUTS>& act) const;

            void add_event_callback(const std::string& event, void(*ev_func)(sfev::CstEv)) const;
            void add_key_pressed_callback(const std::string& key, void(*ev_func)(sfev::CstEv)) const;
            void add_key_released_callback(const std::string& key, void(*ev_func)(sfev::CstEv)) const;

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