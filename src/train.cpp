#include "train.hpp"

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


void App::Train::ev_setup()
{
    View::EventHandler::EVENTHANDLER().ev_setup();
}

void App::Train::draw_setup()
{
    View::Renderer::RENDERER().draw_setup(this->env.get_m());
}

void App::Train::draw_loop()
{
    View::Renderer::RENDERER().draw_loop(this->env.get_m());
}