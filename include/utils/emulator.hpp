#ifndef _EMULATOR_HPP
#define _EMULATOR_HPP

#include <thread>
#include <memory>

#include <nintaco/nintaco.hpp>

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
            virtual inline void ev_setup() {}
            virtual inline void draw_setup() {}
            virtual inline void draw_loop() {}

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
            Event() = default;

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