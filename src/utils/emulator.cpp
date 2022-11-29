#include "utils/emulator.hpp"

nintaco::Emulator::Emulator()
{
    this->rom.run();
    this->api.make();

    nintaco::Api::API().init(this->api.ptr());
    nintaco::State::STATE().init();
    nintaco::Event::EVENT().init();
    nintaco::Action::ACTION().init();
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
        if(! nintaco::Event::EVENT().open()){
            this->api.kill();
            return;
        }
        nintaco::Event::EVENT().focus();
        nintaco::Event::EVENT().process();

        if(! this->loop()){
            this->api.kill();
            return;
        }
        this->draw_loop();
    }
}
