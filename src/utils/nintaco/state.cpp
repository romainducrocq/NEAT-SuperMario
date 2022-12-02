#include "utils/nintaco/state.hpp"

void nintaco::State::init()
{
}

void nintaco::State::load()
{
    std::thread th([&]() {
        nintaco_loadState(nintaco::Api::API().get_api(), &this->sav[0]);
    });
    th.detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
}
