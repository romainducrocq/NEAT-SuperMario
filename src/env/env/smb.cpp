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

    this->cols_[0] = std::max(std::min(this->cols, this->cols_[0]), 0);
    this->cols_[1] = std::max(std::min(this->cols, this->cols - this->cols_[0]), 1);

    this->rows_[0] = (this->rows / 2) + ((this->rows % 2) - 1);
    this->rows_[1] = this->rows / 2;

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

    int i = 0;
    for(int y = (-this->rows_[0] * 16); y <= (this->rows_[1] * 16); y += 16){
        for(int x = (-this->cols_[0] * 16); x < (this->cols_[1] * 16); x += 16){

           [&](int dx, int dy, int y_) {
                for(size_t e = 0; e < this->enemies_xy.size(); e += 2){
                    if(std::abs(this->enemies_xy[e] - dx) <= 8 && std::abs(this->enemies_xy[e + 1] - dy) <= 8){
                        obs[i] = this->scale_to01.at(smb::Smb::feature::ENEMY);
                        return;
                    }
                }

                if(y_ > 11 && i >= this->cols){
                    switch(this->unscale(obs[i - this->cols])){
                        case smb::Smb::feature::HOLE:
                            obs[i] = this->scale_to01.at(smb::Smb::feature::HOLE);
                            return;
                        // case smb::Smb::feature::SAFE:
                        //     obs[i] = this->scale_to01.at(smb::Smb::feature::SAFE);
                        //     return;
                        default:
                            break;
                    }
                }

                if(this->get_tile_t_obs(dx, dy) && dy < 0x1B0){
                    obs[i] = this->scale_to01.at(smb::Smb::feature::SAFE);
                }else if(y_ == 11){
                    obs[i] = this->scale_to01.at(smb::Smb::feature::HOLE);
                }else{
                    obs[i] = this->scale_to01.at(smb::Smb::feature::EMPTY);
                }
           }(x + this->mario_xy[0], y + this->mario_xy[1], (y + this->mario_xy[1] - 48) / 16);

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

    if(y > 11 || y < 0){
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
        return std::max(this->get_frames_fitness() + this->get_distance_fitness() + this->get_win_fitness(), 0.f);
    }
    return 0.f;
}

float smb::Smb::get_frames_fitness() const
{
    return -(static_cast<float>(this->frames) / 2.f);
}

float smb::Smb::get_distance_fitness() const
{
    return static_cast<float>(this->max_mario_x);
}

float smb::Smb::get_win_fitness() const
{
    return static_cast<float>(this->win ? 1 : 0) * 1000.f;
}
