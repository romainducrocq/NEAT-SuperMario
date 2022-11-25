#ifndef _EVAL_HPP
#define _EVAL_HPP

#include "env/conf.hpp"
#include "env/env.hpp"
#include "env/view.hpp"

#include "utils/emulator.hpp"
#include "utils/timer.hpp"

namespace App
{
    class Eval : public Emulator
    {
        private:
            typedef Emulator Super;
            MyEnv::Env env;

        private:
            void ev_setup() override;
            void draw_setup() override;
            void draw_loop() override;

            void setup() override;
            bool loop() override;

            Eval();

        public:
            void run();

        public:
            Eval(const Eval& other) = delete;
            Eval operator=(const Eval& other) = delete;

            static Eval& EVAL()
            {
                static Eval singleton;
                return singleton;
            }
    };
}

#endif