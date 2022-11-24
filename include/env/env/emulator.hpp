#ifndef _ENV_EMULATOR_HPP
#define _ENV_EMULATOR_HPP

#include <thread>
#include <memory>

#include <nintaco/nintaco.hpp>

#include "env/conf.hpp"

namespace nintaco
{
    class Emu
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

        private:
            struct Api
            {
                std::string addr = CONF::ADDR;
                size_t port = CONF::PORT;

                std::unique_ptr<NintacoAPI> api;

                inline void make()
                {
                    this->api = std::unique_ptr<NintacoAPI>(nintaco_newNintacoAPI(&this->addr[0], static_cast<int>(this->port)));
                }

                inline NintacoAPI* get() const
                {
                    return this->api.get();
                }
            };

        public:
            nintaco::Emu::Rom rom;
            nintaco::Emu::Api api;
    };
}


#endif