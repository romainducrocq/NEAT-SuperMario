#include "utils/emulator.hpp"

Emulator::Emulator()
{
    this->rom.run();
    this->api.make();
}

void Emulator::status(nintaco::NintacoAPI*, char* msg)
{
    std::cout << msg << "\n";
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
