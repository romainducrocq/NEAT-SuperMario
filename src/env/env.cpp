#include "env/env.hpp"

/*** DEF INIT FUNC HERE */
void MyEnv::Env::init_func()
{
    this->m.obs_r = &this->Super::mdp.obs;
}

/*** DEF OBS FUNC HERE */
void MyEnv::Env::obs_func()
{
    this->m.smb.obs_func(this->Super::mdp.obs);
}

/*** DEF ACT FUNC HERE */
void MyEnv::Env::act_func()
{
    nintaco::Action::ACTION().act_func(this->Super::mdp.act);
}

/*** DEF DONE FUNC HERE */
void MyEnv::Env::done_func()
{
    this->Super::mdp.done = this->m.smb.done_func();
    if(this->m.smb.get_win_done()){
        Logger::info("WIN (GENERATION " + std::to_string(this->Super::generation) + ")");
    }
}

/*** DEF FITNESS FUNC HERE */
void MyEnv::Env::fitness_func()
{
    this->Super::mdp.fitness = this->m.smb.fitness_func(this->Super::mdp.done);
}

/*** DEF INFO FUNC HERE */
void MyEnv::Env::info_func()
{
    // TODO
}

/*** DEF NOOP FUNC HERE */
void MyEnv::Env::noop_func()
{
}

/*** DEF RESET FUNC HERE */
void MyEnv::Env::reset_func()
{
    nintaco::State::STATE().load();
    this->m.smb.reset_func();
}

/*** DEF STEP FUNC HERE */
void MyEnv::Env::step_func()
{
    this->m.smb.step_func();

    switch (this->Super::mode) {
        case CONF::Mode::TRAIN:
            std::cout << "step train\n";
            break;

        case CONF::Mode::EVAL:
            std::cout << "step eval\n";
            break;

        case CONF::Mode::PLAY:
            // std::cout << "step play\n";
            this->m.smb.obs_func(this->Super::mdp.obs); // TODO rm
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