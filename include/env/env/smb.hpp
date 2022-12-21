#ifndef _ENV_SMB_HPP
#define _ENV_SMB_HPP

#include <cmath>

#include <array>
#include <vector>
#include <unordered_map>

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
                EMPTY, SAFE, HOLE, ENEMY, N
                // EMPTY, SAFE, HOLE, ENEMY, LIFT, JUMP, FIRE, BOSS, N
            };

        private:
            /* OBSERVATION */
            std::unordered_map<smb::Smb::feature, float> scale_to01;

            size_t obs_n = CONF::INPUTS;
            int o_n = 2;

            int max_cols = 13;
            int max_rows = 15;

            int cols = 7;
            int rows;

            std::array<int, 2> cols_ = { 0 };
            std::array<int, 2> rows_ = { 0 };

            std::array<int, 2> mario_xy = { 0 };
            std::vector<int> enemies_xy_t;

            /* ACTION */

            /* DONE */
            bool win = false;
            std::string lvl = CONF::LVL;
            std::unordered_map<std::string, int> win_x = {
                {"1_1", 0}, {"1_2", 2642}, {"1_3", 0}, {"1_4", 2242},
                {"2_1", 0}, {"2_2", 2994}, {"2_3", 0}, {"2_4", 2242},
                {"3_1", 0}, {"3_2", 0},    {"3_3", 0}, {"3_4", 2242},
                {"4_1", 0}, {"4_2", 2994}, {"4_3", 0}, {"4_4", 2754},
                {"5_1", 0}, {"5_2", 0},    {"5_3", 0}, {"5_4", 2242},
                {"6_1", 0}, {"6_2", 0},    {"6_3", 0}, {"6_4", 2242},
                {"7_1", 0}, {"7_2", 2994}, {"7_3", 0}, {"7_4", 3266},
                {"8_1", 0}, {"8_2", 0},    {"8_3", 0}, {"8_4", 4802}
            };

            /* NOOP */
            size_t frames = 0;
            float timer = 0.f;
            float t_cst = 20.f;
            bool timeout = false;
            int max_mario_x = -1;

            /* FITNESS */

        private:
            inline int to1D(int x, int y) const
            {
                return x + y * this->cols;
            }

            inline int unscale(float z) const
            {
                return static_cast<int>(z * (smb::Smb::feature::N - 1) + 0.1f);
            }

            inline int read_cpu(int addr) const
            {
                return nintaco_readCPU(nintaco::Api::API().get_api(), addr);
            }

            inline void write_gamepad(GamepadButtons button, bool value) const
            {
                nintaco_writeGamepad(nintaco::Api::API().get_api(), 0, button, value);
            }

        private:
            /* OBSERVATION */
            void set_mario_obs();
            void set_enemies_obs();
            float get_mario_dx_obs() const;
            float get_mario_dy_obs() const;
            bool get_tile_t_obs(int x, int y) const;

            /* ACTION */
            void set_button_b() const;

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

            /* RESET */
            void reset_func();

            /* STEP */
            void step_func();

            /* OBSERVATION */
            void obs_func(std::array<float, CONF::INPUTS>& obs);

            /* ACTION */
            void act_func() const;

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