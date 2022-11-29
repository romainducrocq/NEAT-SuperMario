#include "utils/nintaco/event.hpp"

void nintaco::Event::init()
{
    if(this->on){
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
    if(this->is() && this->gamepad){
        for(const auto& action : this->actions){
            this->ev_manager->addKeyPressedCallback(this->keys.at(action).first, [&](sfev::CstEv){
                this->keys.at(action).second = true;
            });

            this->ev_manager->addKeyReleasedCallback(this->keys.at(action).first, [&](sfev::CstEv){
                this->keys.at(action).second = false;
            });
        }
    }
}

void nintaco::Event::get_action(std::vector<float>& act) const
{
    if(this->is() && this->gamepad){
        for (size_t i = 0; i < act.size(); i++) {
            act[i] = this->keys.at(this->actions[i]).second ? 1.f : -1.f;
        }
    }
}

void nintaco::Event::add_event_callback(const std::string& event, void(*ev_func)(sfev::CstEv)) const
{
    if(this->is()){
        this->ev_manager->addEventCallback(sfev::evmap.at(event), ev_func);
    }
}

void nintaco::Event::add_key_pressed_callback(const std::string& key, void(*ev_func)(sfev::CstEv)) const
{
    if(this->is()){
        this->ev_manager->addKeyPressedCallback(sfev::kbmap.at(key), ev_func);
    }
}

void nintaco::Event::add_key_released_callback(const std::string& key, void(*ev_func)(sfev::CstEv)) const
{
    if(this->is()){
        this->ev_manager->addKeyReleasedCallback(sfev::kbmap.at(key), ev_func);
    }
}
