#include "utils/emulator.hpp"

Emulator::Emulator()
{
    this->rom.run();
    this->api.make();
}

void Emulator::status(NintacoAPI*, char* msg)
{
    std::cout << msg << "\n";
}

void Emulator::app_run(void(*app_loop_func)(NintacoAPI*))
{
    this->app_setup();
    nintaco_addFrameListener(this->api.ptr(), reinterpret_cast<FrameListener>(&*app_loop_func));
    nintaco_addStatusListener(this->api.ptr(), reinterpret_cast<StatusListener>(&Emulator::status));
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
