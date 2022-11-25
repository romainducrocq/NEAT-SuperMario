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
        void app_run() override;

        void setup() override;
        bool loop() override;

        Train();

    private:
        static void train_loop(NintacoAPI*);

    public:
        void run();

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

#endif
