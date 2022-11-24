#include "utils/emulator.hpp"

Emulator::Emulator()
{
    this->rom.run();
    this->api.make();
}

void Emulator::app_run(void(*app_loop_func)(NintacoAPI*))
{
    this->app_setup();
    nintaco_addFrameListener(this->api.ptr(), reinterpret_cast<FrameListener>(&app_loop_func));

    auto status_func = [](NintacoAPI*, char* msg) { std::cout << msg << "\n"; };
    nintaco_addStatusListener(this->api.ptr(), reinterpret_cast<StatusListener>(&status_func));

    nintaco_run(this->api.ptr());
}

void Emulator::app_setup()
{
    this->ev_setup();
    this->setup();
    this->draw_setup();
}

void Emulator::app_loop()
{
    if(! this->loop()){
        this->api.kill();
    }
    this->draw_loop();
}

/* TODO // remove

    auto func = [](NintacoAPI*){ App::Train::TRAIN(); };


    static void sfunc(NintacoAPI*)
    {
        App::Train::TRAIN();
    }

    auto func = [](NintacoAPI*){ App::Train::TRAIN(); };

    nintaco_addFrameListener(this->api.ptr(), reinterpret_cast<FrameListener>(&sfunc));
    nintaco_addStatusListener(tetrisBot.api, &statusChanged);
    nintaco_run(this->api.ptr());
 */