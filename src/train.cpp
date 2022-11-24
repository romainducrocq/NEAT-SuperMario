#include "train.hpp"

App::Train::Train()
    : env(*this->api.ptr())
{
    this->run();
}

void App::Train::train_loop(nintaco::NintacoAPI*)
{
    std::cout << "hello train\n";
    Train::TRAIN().app_loop();
}

void App::Train::run()
{
    Timer timer;

    std::cout << "\n";
    std::cout << "-------------------------------TRAIN-------------------------------" << "\n";
    std::cout << "\n";

    this->app_run();
}

void App::Train::app_run()
{
    this->app_setup();
    nintaco::addFrameListener(this->Super::api.ptr(), reinterpret_cast<nintaco::FrameListener>(&App::Train::train_loop));
    nintaco::addStatusListener(this->Super::api.ptr(), reinterpret_cast<nintaco::StatusListener>(&Super::status));
    nintaco::run(this->Super::api.ptr());
}

void App::Train::setup()
{
    this->env.init(CONF::Mode::TRAIN);
}

bool App::Train::loop()
{
    return this->env.train();
}
