#include "utils/nintaco/event.hpp"

void nintaco::Event::init(bool on)
{
    if(on){
        this->window = std::make_unique<sf::RenderWindow>();
        this->ev_manager = std::make_unique<sfev::EventManager>(*this->window, true);

        sf::ContextSettings options;
        options.antialiasingLevel = 0;

        this->window->create(sf::VideoMode(1, 1, 1), "SFML", sf::Style::Default, options);
        this->window->setVerticalSyncEnabled(false);

        this->window->setFramerateLimit(0);
    }
}

bool nintaco::Event::is() const
{
    return this->window.get() && this->ev_manager.get();
}

bool nintaco::Event::open() const
{
    if(! this->is()){
        return true;
    }
    return this->window->isOpen();
}

void nintaco::Event::process() const
{
    if(this->is()){
        this->ev_manager->processEvents();
    }
}

void nintaco::Event::focus()
{
    if(this->is() && !this->window->hasFocus()){
        if(this->wmctrl){
            std::thread th([&]() {
                std::system("wmctrl -a SFML");
            });
            th.detach();
            this->wmctrl = false;
        }else{
            this->window->requestFocus();
        }
    }
}

void nintaco::Event::ev_setup()
{
    if(this->is()){
        for(const auto& action : this->actions){
            this->ev_manager->addKeyPressedCallback(this->ev_key.at(action), [&](sfev::CstEv){
                this->ev_state.at(action) = true;
            });

            this->ev_manager->addKeyReleasedCallback(this->ev_key.at(action), [&](sfev::CstEv){
                this->ev_state.at(action) = false;
            });
        }
    }
}

void nintaco::Event::get_action(std::vector<float>& act) const
{
    if(this->is()) {
        for (size_t i = 0; i < act.size(); i++) {
            act[i] = this->ev_state.at(this->actions[i]) ? 1.f : -1.f;
        }
    }
}

const sfev::EventManager& nintaco::Event::get_ev_manager() const { return *this->ev_manager; }
