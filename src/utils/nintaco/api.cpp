#include "utils/nintaco/api.hpp"

void nintaco::Api::init(NintacoAPI* api)
{
    if(! this->api){
        this->api = api;
    }
}

NintacoAPI* nintaco::Api::get_api() const { return this->api; }
