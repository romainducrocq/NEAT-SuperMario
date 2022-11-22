#ifndef _EVAL_HPP
#define _EVAL_HPP

#include "env/conf.hpp"
#include "env/env.hpp"
#include "env/view.hpp"

#include "utils/timer.hpp"

namespace App
{
    class Eval
    {
        private:
            MyEnv::Env env;

        private:
            void run();

            void ev_setup();
            void draw_setup();
            void draw_loop();

            void setup();
            bool loop();

            Eval();

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