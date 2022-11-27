#include "utils/nintaco/state.hpp"

void nintaco::State::load()
{
    nintaco_loadState(nintaco::Api::API().get_api(), &this->sav[0]);
}
