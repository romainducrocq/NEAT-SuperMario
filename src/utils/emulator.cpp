#include "utils/emulator.hpp"

nintaco::Emulator::Emulator()
{
    this->rom.run();
    this->api.make();

    nintaco::Api::API(this->api.ptr());
    nintaco::Event::EVENT().init();
}

void nintaco::Emulator::app_run(void(*app_loop_func)(NintacoAPI*))
{
    this->app_setup();
    nintaco_addFrameListener(this->api.ptr(), app_loop_func);
    nintaco_addStatusListener(this->api.ptr(), [](NintacoAPI*, char* msg) { std::cout << msg << "\n"; } );
    nintaco_run(this->api.ptr());
}

void nintaco::Emulator::app_setup()
{
    this->ev_setup();
    this->setup();
    this->draw_setup();
}

void nintaco::Emulator::app_loop()
{
    if(this->api.ready()){
        if(! nintaco::Event::EVENT().open()){
            this->api.kill();
            return;
        }
        nintaco::Event::EVENT().process();

        if(! this->loop()){
            this->api.kill();
            return;
        }
        this->draw_loop();
    }
}

void nintaco::State::load()
{
    nintaco_loadState(nintaco::Api::API(), &this->sav[0]);
}

void nintaco::Event::init()
{
    this->window = std::make_unique<sf::RenderWindow>();
    this->ev_manager = std::make_unique<sfev::EventManager>(*this->window, true);

    sf::ContextSettings options;
    options.antialiasingLevel = 0;

    this->window->create(sf::VideoMode(1, 1, 1), "", sf::Style::Default, options);
    this->window->setVerticalSyncEnabled(false);

    this->window->setFramerateLimit(0);
}

bool nintaco::Event::open()
{
    return this->window->isOpen();
}

void nintaco::Event::process()
{
    this->ev_manager->processEvents();
}

void nintaco::Event::ev_setup()
{
    auto add_func = [&](sf::Keyboard::Key key) {
        this->ev_manager->addKeyPressedCallback(key, [&](sfev::CstEv){
            this->keys.at(key) = true;
        });

        this->ev_manager->addKeyReleasedCallback(key, [&](sfev::CstEv){
            this->keys.at(key) = false;
        });
    };

    for(const auto& action : this->actions){
        switch(action){
            case CONF::Action::A:
                add_func(sfev::kbmap.at(this->key_a));
                break;

            case CONF::Action::B:
                add_func(sfev::kbmap.at(this->key_b));
                break;

            case CONF::Action::UP:
                add_func(sfev::kbmap.at(this->key_up));
                break;

            case CONF::Action::DOWN:
                add_func(sfev::kbmap.at(this->key_down));
                break;

            case CONF::Action::LEFT:
                add_func(sfev::kbmap.at(this->key_left));
                break;

            case CONF::Action::RIGHT:
                add_func(sfev::kbmap.at(this->key_right));
                break;

            case CONF::Action::START:
                add_func(sfev::kbmap.at(this->key_start));
                break;

            case CONF::Action::SELECT:
                add_func(sfev::kbmap.at(this->key_select));
                break;
        }
    }
}

void nintaco::Event::get_action(std::vector<float>& act)
{
    auto it = act.begin();

    auto act_func = [&act, &it](bool state, bool other) {
        if(it != act.end()){
            *it = state && !other ? 1.f : -1.f;
            it++;
        }
    };

    for(const auto& action : this->actions){
        switch(action){
            case CONF::Action::A:
                act_func(this->keys.at(sfev::kbmap.at(this->key_a)), false);
                break;

            case CONF::Action::B:
                act_func(this->keys.at(sfev::kbmap.at(this->key_b)), false);
                break;

            case CONF::Action::UP:
                act_func(this->keys.at(sfev::kbmap.at(this->key_up)),
                         this->keys.at(sfev::kbmap.at(this->key_down)));
                break;

            case CONF::Action::DOWN:
                act_func(this->keys.at(sfev::kbmap.at(this->key_down)),
                         this->keys.at(sfev::kbmap.at(this->key_up)));
                break;

            case CONF::Action::LEFT:
                act_func(this->keys.at(sfev::kbmap.at(this->key_left)),
                         this->keys.at(sfev::kbmap.at(this->key_right)));
                break;

            case CONF::Action::RIGHT:
                act_func(this->keys.at(sfev::kbmap.at(this->key_right)),
                         this->keys.at(sfev::kbmap.at(this->key_left)));
                break;

            case CONF::Action::START:
                act_func(this->keys.at(sfev::kbmap.at(this->key_start)), false);
                break;

            case CONF::Action::SELECT:
                act_func(this->keys.at(sfev::kbmap.at(this->key_select)), false);
                break;
        }
    }
}

const sfev::EventManager& nintaco::Event::get_ev_manager() const { return *this->ev_manager; }
