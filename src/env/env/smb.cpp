#include "env/env/smb.hpp"

smb::Smb::Smb()
{
    /* OBSERVATION */
    for(size_t i = 0; i < smb::Smb::feature::N; i++){
        this->scale_to01.insert({static_cast<smb::Smb::feature>(i),
                                 static_cast<float>(i) / static_cast<float>(smb::Smb::feature::N - 1)});
    }

    this->cols = std::max(std::min(this->max_cols, this->cols), 1);
    this->rows = std::max(std::min(this->max_rows, static_cast<int>(this->obs_n) / this->cols), 1);

    this->cols_l = std::max(std::min(this->cols, this->cols_l), 0);
    this->cols_r = std::max(std::min(this->cols, this->cols - this->cols_l), 1);

    /* DONE */

    /* NOOP */

    /* FITNESS */
}

/* RESET */

void smb::Smb::reset_func()
{
    /* OBSERVATION */

    /* DONE */
    this->win = false;

    /* NOOP */
    this->frames = 0;
    this->timer = this->t_cst;
    this->timeout = false;
    this->max_mario_x = -1;

    /* FITNESS */
}

/* STEP */

void smb::Smb::step_func()
{
    /* OBSERVATION */
    this->set_mario_obs();

    /* DONE */

    /* NOOP */
    this->set_timeout_noop();

    /* FITNESS */
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
                    obs[i] = this->scale_to01.at(smb::Smb::feature::MARIO);
                    return;
                }

                for(size_t e = 0; e < this->enemies_xy.size(); e += 2){
                    if(std::abs(this->enemies_xy[e] - dx) <= 8 && std::abs(this->enemies_xy[e + 1] - y) <= 8){
                        obs[i] = this->scale_to01.at(smb::Smb::feature::ENEMY);
                        return;
                    }
                }

                obs[i] = this->get_tile_t_obs(dx, y) ? this->scale_to01.at(smb::Smb::feature::SAFE) :
                                                       this->scale_to01.at(smb::Smb::feature::EMPTY);
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

/* DONE */

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

/* NOOP */

bool smb::Smb::noop_func() const
{
    return this->timeout;
}

void smb::Smb::set_timeout_noop()
{
    this->frames++;

    if(this->mario_xy[0] > this->max_mario_x){
        this->max_mario_x = this->mario_xy[0];
        this->timer = this->t_cst;
    }

    this->timer -= 1.f;

    if(this->timer + (static_cast<float>(this->frames) / 4.f) <= 0){
        this->timeout = true;
    }
}

/* FITNESS */

float smb::Smb::fitness_func(bool done) const
{
    if(done){
        return std::max(this->get_frames_fitness() + this->get_distance_fitness() + this->get_win_fitness(), 0.00001f);
    }
    return 0.f;
}

float smb::Smb::get_frames_fitness() const
{
    return (-std::pow(static_cast<float>(this->frames), 1.5f));
}

float smb::Smb::get_distance_fitness() const
{
    return std::pow(static_cast<float>(this->mario_xy[0]), 1.8f) +
        (std::min(std::max(static_cast<float>(this->mario_xy[0]) - 50.f, 0.f), 1.f) * 2500.f);
}

float smb::Smb::get_win_fitness() const
{
    return static_cast<float>(this->win ? 1 : 0) * 1000000.f;
}
