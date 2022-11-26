#include "utils/emulator.hpp"

nintaco::Emulator::Emulator()
{
    this->rom.run();
    this->api.make();

    nintaco::Api::API(this->api.ptr());
}

void nintaco::Emulator::app_run(void(*app_loop_func)(NintacoAPI*))
{
    this->app_setup();
    nintaco_addFrameListener(this->api.ptr(), app_loop_func);
    nintaco_addStatusListener(this->api.ptr(), [](NintacoAPI*, char* msg) { std::cout << msg << "\n"; } );
    nintaco_run(this->api.ptr());
}

void nintaco::Emulator::app_setup()
{
    this->ev_setup();
    this->setup();
    this->draw_setup();
}

void nintaco::Emulator::app_loop()
{
    if(this->api.ready()){
        if(! this->loop()){
            this->api.kill();
        }
        this->draw_loop();
    }
}

void nintaco::State::load()
{
    nintaco_loadState(nintaco::Api::API(), &this->sav[0]);
}
