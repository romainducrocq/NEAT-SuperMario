#ifndef _EMULATOR_HPP
#define _EMULATOR_HPP

#include <cassert>

#include <thread>
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
    class Emulator
    {
        private:
            struct Rom
            {
                std::string sh1 = "../../opt/java/jre1.8.0_latest/bin/java -jar "
                                  "../../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar "
                                  "../../res/rom/" + CONF::ROM + "." + CONF::EXT;

                inline void run()
                {
                    std::thread th([&]() {
                        std::system(&this->sh1[0]);
                    });
                    th.detach();
                }
            };

            struct Api
            {
                std::string addr = CONF::ADDR;
                size_t port = CONF::PORT;

                std::unique_ptr<NintacoAPI> api;

                inline void make()
                {
                    this->api = std::unique_ptr<NintacoAPI>(
                            nintaco_newNintacoAPI(&this->addr[0], static_cast<int>(this->port)));
                }

                inline void kill() const
                {
                    this->api->running = false;
                }

                inline bool ready() const
                {
                    return this->api->running && this->api->in && this->api->out && this->api->in->alive && this->api->out->alive;
                }

                inline NintacoAPI* ptr() const
                {
                    return this->api.get();
                }
            };

        private:
            Emulator::Rom rom;
            Emulator::Api api;

        protected:
            void app_run(void(*app_loop_func)(NintacoAPI*));

        private:
            void app_setup();

        protected:
            virtual void app_loop() final;

        protected:
            virtual inline void ev_setup() = 0;
            virtual inline void draw_setup() = 0;
            virtual inline void draw_loop() = 0;

            virtual void setup() = 0;
            virtual bool loop() = 0;

        public:
            Emulator();
    };

    class Api
    {
        private:
            NintacoAPI* api = nullptr;

        private:
            Api() = default;

        public:
            Api(const Api &other) = delete;
            Api operator=(const Api &other) = delete;

            static NintacoAPI* &API(NintacoAPI* api=nullptr)
            {
                static Api singleton;
                if(api){
                    singleton.api = api;
                }
                return singleton.api;
            }
    };

    class State
    {
        private:
            std::string sav = "../../res/sav/" + CONF::ROM + "_" + CONF::SAV + ".save";

        private:
            State() = default;

        public:
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
            void init();
            bool open();
            void process();

            void ev_setup();
            void get_action(std::vector<float>& act);

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

    class Action
    {
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
