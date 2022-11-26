#ifndef _TRAIN_HPP
#define _TRAIN_HPP

#include "env/conf.hpp"
#include "env/env.hpp"
#include "env/view.hpp"

#include "utils/emulator.hpp"
#include "utils/timer.hpp"

namespace App
{
    class Train : public nintaco::Emulator
    {
    private:
        typedef nintaco::Emulator Super;
        MyEnv::Env env;

    private:
        void setup() override;
        bool loop() override;

        Train();

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
