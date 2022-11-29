#include "env/view.hpp"

/*** DEF EVENT SETUP HERE */
void View::EventHandler::ev_setup()
{
    nintaco::Event::EVENT().add_key_pressed_callback(
            View::EventHandler::EVENTHANDLER().ev_state.debug.first, [](sfev::CstEv){
        View::EventHandler::EVENTHANDLER().ev_state.debug.second = true;
    });

    nintaco::Event::EVENT().add_key_released_callback(
            View::EventHandler::EVENTHANDLER().ev_state.debug.first, [](sfev::CstEv){
        View::EventHandler::EVENTHANDLER().ev_state.debug.second = false;
    });

    nintaco::Event::EVENT().ev_setup();
}

/*** DEF ACTION HANDLER HERE */
void View::EventHandler::get_action(std::vector<float>& act)
{
    nintaco::Event::EVENT().get_action(act);
}

/*** DEF DRAW SETUP HERE */
void View::Renderer::draw_setup(const MyEnv::Model& /*m*/)
{
}

/*** DEF DRAW LOOP HERE */
void View::Renderer::draw_loop(const MyEnv::Model& /*m*/)
{
}

/*** DEF DRAW FUNCS HERE */

