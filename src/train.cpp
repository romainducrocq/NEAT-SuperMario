#include "train.hpp"

App::Train::Train()
{
    this->run();
}

void App::Train::run()
{
    Timer timer;

    std::cout << "\n";
    std::cout << "-------------------------------TRAIN-------------------------------" << "\n";
    std::cout << "\n";

    std::thread th([&]() {
        this->setup();

        while(this->loop()){}
    });

    if(th.joinable()){
        th.join();
    }
}

void App::Train::setup()
{
    this->env.init(CONF::Mode::TRAIN);
}

bool App::Train::loop()
{
    return this->env.train();
}
