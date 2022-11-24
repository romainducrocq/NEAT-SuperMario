#ifndef _PLAY_HPP
#define _PLAY_HPP

#include <iostream>
#include <cstring>
#include <sstream>

#include "env/conf.hpp"
#include "env/env.hpp"
#include "env/view.hpp"

#include "utils/emulator.hpp"
#include "utils/timer.hpp"

namespace App
{
    class Play : public Emulator
    {
        private:
            typedef Emulator Super;
            MyEnv::Env env;

        private:
            void init();

            void reset();
            void step();

            bool play();

        private:
            void run();

            void app_run() override;

            void ev_setup() override;
            void draw_setup() override;
            void draw_loop() override;

            void setup() override;
            bool loop() override;

            Play();

        private:
            static void play_loop(nintaco::NintacoAPI*);

        public:
            Play(const Play &other) = delete;

            Play operator=(const Play &other) = delete;

            static Play &PLAY()
            {
                static Play singleton;
                return singleton;
            }
    };
}

#endif