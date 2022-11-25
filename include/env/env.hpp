#ifndef _ENV_ENV_HPP
#define _ENV_ENV_HPP

#include <memory>

#include <nintaco/nintaco.hpp>

#include "neat/neat.hpp"

#include "utils/logger.hpp"

/*** ADD INCLUDE HERE */


namespace App { class Play; }

namespace MyEnv
{
    /*** DEC MODEL HERE */
    struct Model
    {
    };

    class Env : public Neat
    {
        private:
            typedef Neat Super;
            friend class App::Play;

        private:
            MyEnv::Model m;

            NintacoAPI& api;
            std::string sav;

        private:
            void init_func() override;

            void obs_func() override;

            void act_func() override;

            void done_func() override;

            void fitness_func() override;

            void info_func() override;

            void noop_func() override;

            void reset_func() override;

            void step_func() override;

            void reset_render_func() override;

            void step_render_func() override;

        public:
            Env() = delete;
            inline Env(NintacoAPI& api, std::string& sav)
                : api(api), sav(sav)
            {
            }

            inline const MyEnv::Model &get_m() const
            {
                return this->m;
            }
    };
}

#endif