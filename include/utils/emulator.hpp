#ifndef _EMULATOR_HPP
#define _EMULATOR_HPP

#include <thread>
#include <memory>

#include <nintaco/nintaco.hpp>

#include "env/conf.hpp"

class Emulator
{
    private:
        struct Rom
        {
            std::string sh1 = "../../opt/java/jre1.8.0_latest/bin/java -jar "
                              "../../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar "
                              "../../res/rom/" + CONF::ROM + "." + CONF::EXT;

            std::string sav = "../../res/sav/" + CONF::ROM + "_" + CONF::SAV + ".save";

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

            std::unique_ptr<nintaco::NintacoAPI> api;

            inline void make()
            {
                this->api = std::unique_ptr<nintaco::NintacoAPI>(
                        nintaco::newNintacoAPI(&this->addr[0], static_cast<int>(this->port)));
            }

            inline void kill() const
            {
                this->api->running = false;
            }

            inline nintaco::NintacoAPI* ptr() const
            {
                return this->api.get();
            }
        };

    private:
        Emulator::Rom rom;

    protected:
        Emulator::Api api;

    protected:
        virtual void app_setup() final;
        virtual void app_loop() final;

        virtual void app_run() = 0;

    protected:
        virtual inline void ev_setup() {}
        virtual inline void draw_setup() {}
        virtual inline void draw_loop() {}

        virtual void setup() = 0;
        virtual bool loop() = 0;

    public:
        Emulator();

    protected:
        static void status(nintaco::NintacoAPI*, char* msg);
};

#endif