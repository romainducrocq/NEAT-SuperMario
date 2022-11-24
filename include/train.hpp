#ifndef _TRAIN_HPP
#define _TRAIN_HPP

#include "env/conf.hpp"
#include "env/env.hpp"
#include "env/view.hpp"

#include "utils/emulator.hpp"
#include "utils/timer.hpp"

namespace App
{
    class Train : public Emulator
    {
    private:
        typedef Emulator Super;
        MyEnv::Env env;

    private:
        void run();

        void ev_setup() override;
        void draw_setup() override;
        void draw_loop() override;

        void setup() override;
        bool loop() override;

        Train();

    public:
        Train(const Train& other) = delete;
        Train operator=(const Train& other) = delete;

        static Train& TRAIN()
        {
            static Train singleton;
            return singleton;
        }
    };
}


/*
namespace App
{
    class Train : public Emulator
    {
        private:
            typedef Emulator Super;
            MyEnv::Env env;

        private:
            void run();

            void ev_setup() override;
            void draw_setup() override;
            void draw_loop() override;

            void setup() override;
            bool loop() override;

            Train();

        public:
            Train(const Train& other) = delete;
            Train operator=(const Train& other) = delete;

            static Train& TRAIN()
            {
                static Train singleton;
                return singleton;
            }
    };
}
*/

#endif
