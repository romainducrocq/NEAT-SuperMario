#include "env/env.hpp"

/*** DEF INIT FUNC HERE */
void MyEnv::Env::init_func()
{
}

/*** DEF OBS FUNC HERE */
void MyEnv::Env::obs_func()
{
}

/*** DEF ACT FUNC HERE */
void MyEnv::Env::act_func()
{
    nintaco::Action::ACTION().act_func(this->Super::mdp.act);
}

/*** DEF DONE FUNC HERE */
void MyEnv::Env::done_func()
{
}

/*** DEF FITNESS FUNC HERE */
void MyEnv::Env::fitness_func()
{
}

/*** DEF INFO FUNC HERE */
void MyEnv::Env::info_func()
{
}

/*** DEF NOOP FUNC HERE */
void MyEnv::Env::noop_func()
{
}

/*** DEF RESET FUNC HERE */
void MyEnv::Env::reset_func()
{
    nintaco::State::STATE().load();
}

/*** DEF STEP FUNC HERE */
void MyEnv::Env::step_func()
{
    switch (this->Super::mode) {
        case CONF::Mode::TRAIN:
            std::cout << "step train\n";
            break;

        case CONF::Mode::EVAL:
            std::cout << "step eval\n";
            break;

        case CONF::Mode::PLAY:
            // std::cout << "step play\n";
            break;
        default:
            break;
    }
}

/*** DEF RESET RENDER FUNC HERE */
void MyEnv::Env::reset_render_func()
{
}

/*** DEF STEP RENDER FUNC HERE */
void MyEnv::Env::step_render_func()
{
}