#ifndef _ENV_ENV_HPP
#define _ENV_ENV_HPP

#include <nintaco/nintaco.hpp>

#include "neat/neat.hpp"

#include "utils/nintaco/api.hpp"
#include "utils/nintaco/state.hpp"
#include "utils/nintaco/action.hpp"

#include "utils/logger.hpp"

/*** ADD INCLUDE HERE */
#include <array>

#include "env/env/smb.hpp"

#include "env/conf.hpp"

namespace App { class Play; }

namespace MyEnv
{
    /*** DEC MODEL HERE */
    struct Model
    {
        std::array<float, CONF::INPUTS>* obs_r = nullptr;

        smb::Smb smb = smb::Smb(CONF::INPUTS);
    };

    class Env : public Neat
    {
        private:
            typedef Neat Super;
            friend class App::Play;

        private:
            MyEnv::Model m;

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
            Env() = default;

            inline const MyEnv::Model &get_m() const
            {
                return this->m;
            }
    };
}

#endif