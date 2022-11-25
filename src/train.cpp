#include "train.hpp"

App::Train::Train()
    : env(*this->api.ptr(), this->rom.sav)
{
}

void App::Train::run()
{
    Timer timer;

    std::cout << "\n";
    std::cout << "-------------------------------TRAIN-------------------------------" << "\n";
    std::cout << "\n";

    this->Super::app_run([](NintacoAPI*) { Train::TRAIN().app_loop(); } );
}

void App::Train::setup()
{
    this->env.init(CONF::Mode::TRAIN);
}

bool App::Train::loop()
{
    return this->env.train();
}
