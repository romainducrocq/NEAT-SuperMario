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
            /* OBSERVATION */
            size_t obs_n = CONF::INPUTS;

            int max_cols = 13;
            int max_rows = 15;

            int cols = 10;
            int rows;

            int cols_l = 3;
            int cols_r;

            std::array<int, 2> mario_xy = { 0 };
            std::vector<int> enemies_xy;

            /* DONE */
            bool win = false;

            /* NOOP */
            size_t frames = 0;
            float timer = 0.f;
            float t_cst = 20.f;
            bool timeout = false;
            int max_mario_x = -1;

            /* FITNESS */

        private:
            inline size_t to1D(int x, int y) const
            {
                return x + y * this->cols;
            }

            inline int read_cpu(int addr) const
            {
                return nintaco_readCPU(nintaco::Api::API().get_api(), addr);
            }

        private:
            /* OBSERVATION */
            void set_mario_obs();
            void set_enemies_obs();
            bool get_tile_t_obs(int x, int y) const;

            /* DONE */
            void set_win_done();
            bool get_die_done() const;

            /* NOOP */
            void set_timeout_noop();

            /* FITNESS */
            float get_frames_fitness() const;
            float get_distance_fitness() const;
            float get_win_fitness() const;

        public:
            Smb();

            void reset_func();
            void step_func();

            /* OBSERVATION */
            void obs_func(std::array<float, CONF::INPUTS>& obs);

            /* DONE */
            bool done_func();
            bool get_win_done() const;

            /* NOOP */
            bool noop_func() const;

            /* FITNESS */
            float fitness_func(bool done) const;
    };
}

#endif