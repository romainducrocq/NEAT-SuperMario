#include "utils/nintaco/state.hpp"

void nintaco::State::init()
{
}

void nintaco::State::reset()
{
    if(this->ini){
        nintaco::State::STATE().load();
        std::thread th([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            this->quick_save();
        });
        th.detach();

        this->ini = false;
    }else{
        this->quick_load();
    }
}

void nintaco::State::load()
{
    nintaco_loadState(nintaco::Api::API().get_api(), &this->sav[0]);
}

void nintaco::State::quick_save() const
{
    nintaco_quickSaveState(nintaco::Api::API().get_api(), 1);
}

void nintaco::State::quick_load() const
{
    nintaco_quickLoadState(nintaco::Api::API().get_api(), 1);
}