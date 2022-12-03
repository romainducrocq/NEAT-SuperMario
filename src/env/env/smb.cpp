#include "env/env/smb.hpp"

smb::Smb::Smb()
{
    /* OBSERVATION */

    this->cols = std::max(std::min(this->max_cols, this->cols), 1);
    this->rows = std::max(std::min(this->max_rows, static_cast<int>(this->obs_n) / this->cols), 1);

    this->cols_l = std::max(std::min(this->cols, this->cols_l), 0);
    this->cols_r = std::max(std::min(this->cols, this->cols - this->cols_l), 1);
}

/* RESET */

void smb::Smb::reset_func()
{
    this->win = false;
}

/* STEP */

void smb::Smb::step_func()
{
    this->set_mario_obs();
}

/* OBSERVATION */

void smb::Smb::obs_func(std::array<float, CONF::INPUTS>& obs)
{
    this->set_enemies_obs();

    size_t i = 0;
    for(int y = ((15 - this->rows) * 16); y < (15 * 16); y += 16){
        for(int x = (-this->cols_l * 16); x < (this->cols_r * 16); x += 16){

            [&](int dx) {
                if(x == 0 && std::abs(this->mario_xy[1] - y + 16) <= 8){
                    obs[i] = smb::Smb::feature::MARIO;
                    return;
                }

                for(size_t e = 0; e < this->enemies_xy.size(); e += 2){
                    if(std::abs(this->enemies_xy[e] - dx) <= 8 && std::abs(this->enemies_xy[e + 1] - y) <= 8){
                        obs[i] = smb::Smb::feature::ENEMY;
                        return;
                    }
                }

                obs[i] = this->get_tile_t_obs(dx, y) ? smb::Smb::feature::SAFE : smb::Smb::feature::EMPTY;
            }(x + this->mario_xy[0]);

            i++;
        }
    }
}

void smb::Smb::set_mario_obs()
{
    this->mario_xy[0] = (this->read_cpu(0x6D) * 0x100) + this->read_cpu(0x86);
    this->mario_xy[1] = this->read_cpu(0x03B8) + 16;
}

void smb::Smb::set_enemies_obs()
{
    this->enemies_xy.clear();
    for(int i = 0; i < 5; i++){
        if(this->read_cpu(0xF + i)){
            enemies_xy.push_back((this->read_cpu(0x6E + i) * 0x100) + this->read_cpu(0x87 + i));
            enemies_xy.push_back(this->read_cpu(0xCF + i) + 24);
        }
    }
}

bool smb::Smb::get_tile_t_obs(int x, int y) const
{
    x += 8;
    y -= 16;

    int page = (x / 256) % 2;
    x = (x % 256) / 16;
    y = (y - 32) / 16;

    if(y >= 13 || y < 0){
        return false;
    }

    switch(this->read_cpu(0x500 + (page * 13 * 16) + (y * 16) + x)){
        case 0:
        case 0xC2:
        case 0x25:
            return false;

        default:
            return true;
    }
}

/* DONE */ // TODO timeout

bool smb::Smb::done_func()
{
    this->set_win_done();
    return this->get_die_done() || this->win;
}

void smb::Smb::set_win_done()
{
    this->win = this->read_cpu(0x001D) == 3;
}

bool smb::Smb::get_die_done() const
{
    if(this->read_cpu(0xB5) >= 2){
        return true;
    }

    int addr = this->read_cpu(0x0E);
    if(addr == 0x0B || addr == 0x06){
        return true;
    }

    return false;
}

bool smb::Smb::get_win_done() const
{
    return this->win;
}

/* FITNESS */

float smb::Smb::fitness_func(bool done, size_t steps) const
{
    if(done){
        return std::max(this->get_frames_fitness(steps) + this->get_distance_fitness() + this->get_score_fitness() +
            this->get_win_fitness(), 0.00001f);
    }
    return 0.f;
}

float smb::Smb::get_frames_fitness(size_t steps) const
{
    int frames = static_cast<int>(steps);
    return std::pow(static_cast<float>(frames), 1.5f);
}

float smb::Smb::get_distance_fitness() const
{
    int distance = this->mario_xy[0];
    return std::pow(static_cast<float>(distance), 1.9f) -
        (std::min(std::max(static_cast<float>(distance) - 50.f, 0.f), 1.f) * 2000.f);
}

float smb::Smb::get_score_fitness() const
{
    int score = 0;
    int mult = 10;

    for(int addr = 0x07DC; addr >= 0x07D7; addr -= 1){
        score += this->read_cpu(addr) * mult;
        mult *= 10;
    }

    return std::pow(static_cast<float>(score), 2.f);
}

float smb::Smb::get_win_fitness() const
{
    int win = this->win ? 1 : 0;
    return static_cast<float>(win) * 1000000.f;
}
