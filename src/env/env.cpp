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
        this->m.win_cnt++;
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
    switch(this->Super::mode){

        case CONF::Mode::TRAIN:
            std::cout << "GENERATION  : " << this->Super::generation << " / " <<
                (this->Super::max_generation_train > 0 ? std::to_string(this->Super::max_generation_train) :
                                                         "INF") << "\n";
            std::cout << "MAX FITNESS : " << this->Super::max_fitness << "\n";
            std::cout << "MVG AVG     : " << this->Super::mvg_avg.get() << "\n";
            std::cout << "#   WIN     : " << this->m.win_cnt << "\n";
            std::cout << "\n";
            break;

        case CONF::Mode::EVAL:
        case CONF::Mode::PLAY:
            std::cout << "EPOCH   : " << this->Super::epoch << " / " <<
                (this->Super::max_epoch_eval > 0 ? std::to_string(this->Super::max_epoch_eval) :
                                                   "INF") << "\n";
            std::cout << "FITNESS : " << this->Super::mdp.fitness << "\n";
            std::cout << "MVG AVG : " << this->Super::mvg_avg.get() << "\n";
            std::cout << "DID WIN : " << (this->m.win_cnt ? "YES" : "NO") << "\n";
            std::cout << "\n";
            break;

        default:
            break;
    }

    this->m.win_cnt = 0;
}

/*** DEF NOOP FUNC HERE */
void MyEnv::Env::noop_func()
{
    this->Super::is_noop = this->m.smb.noop_func();
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
}

/*** DEF RESET RENDER FUNC HERE */
void MyEnv::Env::reset_render_func()
{
}

/*** DEF STEP RENDER FUNC HERE */
void MyEnv::Env::step_render_func()
{
}