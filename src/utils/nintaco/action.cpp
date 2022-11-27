#include "utils/nintaco/action.hpp"

void nintaco::Action::init()
{
    for(size_t i = 0; i < this->actions.size(); i++){
        switch(this->actions[i]){
            case CONF::Action::UP:
                this->noops[0].act1 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::DOWN:
                this->noops[0].act2 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::LEFT:
                this->noops[1].act1 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::RIGHT:
                this->noops[1].act2 = std::make_unique<size_t>(i);
                break;

            default:
                break;
        }
    }
}

void nintaco::Action::act_func(std::vector<float>& act) const
{
    for(const auto& noop : noops)
    {
        if(noop.is()){
            if(nintaco::Action::Output::activate(act[*noop.act1]) &&
               nintaco::Action::Output::activate(act[*noop.act2]))
            {
                act[*noop.act1] = -1.f;
                act[*noop.act2] = -1.f;
            }
        }
    }

    /*
    for (const auto& z : act) {
        if(nintaco::Action::Output::activate(z)){
            std::cout << "act" << "\n";
        }
    }
     */

    for(size_t i = 0; i < act.size(); i++){
        switch (i) {
            case 0:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "A" << "\n";
                }
                break;
            case 1:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "B" << "\n";
                }
                break;
            case 2:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "UP" << "\n";
                }
                break;
            case 3:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "DOWN" << "\n";
                }
                break;
            case 4:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "LEFT" << "\n";
                }
                break;
            case 5:
                if(nintaco::Action::Output::activate(act[i])) {
                    std::cout << "RIGHT" << "\n";
                }
                break;
        }
    }
}