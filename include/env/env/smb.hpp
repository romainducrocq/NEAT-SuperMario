#ifndef _ENV_SMB_HPP
#define _ENV_SMB_HPP

#include <cmath>

#include <array>
#include <vector>

#include <nintaco/nintaco.hpp>

#include "utils/nintaco/api.hpp"

#include "env/conf.hpp"

namespace View { class Renderer; }

namespace smb
{
    class Smb
    {
        private:
            friend class View::Renderer;

        private:
            enum feature{
                EMPTY, SAFE, ENEMY, MARIO
            };

        private:
            size_t obs_n = CONF::INPUTS;

            int max_cols = 13;
            int max_rows = 15;

            int cols = 10;
            int rows;

            int cols_l = 3;
            int cols_r;

        private:
            std::array<int, 2> mario_xy = { 0 };
            std::vector<int> enemies_xy;

        private:
            inline size_t to1D(int x, int y) const
            {
                return x + y * this->cols;
            }

            inline int read_cpu(int addr) const
            {
                return nintaco_readCPU(nintaco::Api::API().get_api(), addr);
            }

            inline bool read_gamepad(int gamepad, int button) const
            {
                return nintaco_readGamepad(nintaco::Api::API().get_api(), gamepad, button);
            }

        private:
            void set_mario_obs();
            void set_enemies_obs();
            bool get_tile_t_obs(int x, int y) const;

            float get_frames_fitness(size_t steps) const;
            float get_distance_fitness() const;
            float get_score_fitness() const;
            float get_win_fitness() const;

            bool get_win_done(bool& win) const;
            bool get_die_done() const;

        public:
            Smb();

            void obs_func(std::array<float, CONF::INPUTS>& obs);
            float fitness_func(bool done, size_t steps) const;
            bool done_func(bool& win) const;
            bool noop_func() const;
    };
}

#endif