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
void View::EventHandler::get_action(std::array<float, CONF::OUTPUTS>& act)
{
    nintaco::Event::EVENT().get_action(act);
}

/*** DEF DRAW SETUP HERE */
void View::Renderer::draw_setup(const MyEnv::Model& /*m*/)
{
}

/*** DEF DRAW LOOP HERE */
void View::Renderer::draw_loop(const MyEnv::Model& m)
{
    if(View::EventHandler::EVENTHANDLER().get_ev_state().debug.second){
        if (WIFEXITED(std::system("clear"))){
            std::cout << std::endl;
        }
        for(size_t y = 0; y < m.smb.rows; y++){
            for(size_t x = 0; x < m.smb.cols; x++){
                switch(static_cast<size_t>((*m.obs_r)[m.smb.to1D(x, y)])){
                    case smb::Smb::OBS::EMPTY:
                        std::cout << "\033[1;34m" << "# " << "\033[0m"; // BLUE
                        break;

                    case smb::Smb::OBS::SAFE:
                        std::cout << "\033[0;33m" << "# " << "\033[0m"; // BROWN ORANGE
                        break;

                    case smb::Smb::OBS::ENEMY:
                        std::cout << "\033[0;31m" << "# " << "\033[0m"; // RED
                        break;

                    case smb::Smb::OBS::MARIO:
                        std::cout << "\033[0;32m" << "# " << "\033[0m"; // GREEN
                        break;
                }
            }
            std::cout << "\n";
        }
    }
}

/*** DEF DRAW FUNCS HERE */

