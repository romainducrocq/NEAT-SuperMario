#include "env/view.hpp"

/*** DEF EVENT SETUP HERE */
void View::EventHandler::ev_setup()
{
    nintaco::Event::EVENT().add_key_released_callback(
            View::EventHandler::EVENTHANDLER().ev_state.debug.first, [](sfev::CstEv){
                View::EventHandler::EVENTHANDLER().ev_state.debug.second =
                    ! View::EventHandler::EVENTHANDLER().ev_state.debug.second;
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
    this->debug_timer = std::chrono::high_resolution_clock::now();
}

/*** DEF DRAW LOOP HERE */
void View::Renderer::draw_loop(const MyEnv::Model& m)
{
    if(View::EventHandler::EVENTHANDLER().get_ev_state().debug.second &&
       (this->mode == CONF::Mode::TRAIN || this->mode == CONF::Mode::EVAL) &&
       std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - this->debug_timer).count()
       > this->debug_sleep){

        if(WIFEXITED(std::system("clear"))){
            std::cout << std::endl;
        }
        for(int y = 0; y < m.smb.rows; y++){
            for(int x = 0; x < m.smb.cols; x++){
                switch(m.smb.unscale((*m.obs_r)[m.smb.to1D(x, y)])){
                    case smb::Smb::feature::EMPTY:
                        std::cout << "\033[1;34m" << "# " << "\033[0m"; // BLUE
                        break;

                    case smb::Smb::feature::SAFE:
                        std::cout << "\033[0;33m" << "# " << "\033[0m"; // BROWN ORANGE
                        break;

                    case smb::Smb::feature::ENEMY:
                        std::cout << "\033[0;31m" << "# " << "\033[0m"; // RED
                        break;

                    case smb::Smb::feature::HOLE:
                        std::cout << "\033[0;32m" << "# " << "\033[0m"; // GREEN
                        break;
                }
            }
            std::cout << "\n";
        }

        std::cout << "\n";
        int i = m.smb.rows * m.smb.cols;
        std::cout << "* dx: " << (*m.obs_r)[i++] << "\n";
        std::cout << "* dy: " << (*m.obs_r)[i++] << "\n";

        this->debug_timer = std::chrono::high_resolution_clock::now();
    }
}

/*** DEF DRAW FUNCS HERE */

