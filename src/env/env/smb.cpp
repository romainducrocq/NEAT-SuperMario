#include "env/env/smb.hpp"

smb::Smb::Smb(size_t obs_n)
{
    this->cols = std::max(std::min(this->max_cols, this->cols), 1);
    this->rows = std::max(std::min(this->max_rows, static_cast<int>(obs_n) / this->cols), 1);

    this->cols_l = std::max(std::min(this->cols, this->cols_l), 0);
    this->cols_r = std::max(std::min(this->cols, this->cols - this->cols_l), 1);
}

/* OBSERVATION */

void smb::Smb::obs_func(std::array<float, CONF::INPUTS>& obs)
{
    this->set_mario();
    this->set_enemies();

    size_t i = 0;
    for(int y = ((15 - this->rows) * 16); y < (15 * 16); y += 16){
        for(int x = (-this->cols_l * 16); x < (this->cols_r * 16); x += 16){

            [&](int dx) {
                if(x == 0 && std::abs(this->mario_xy[1] - y + 16) <= 8){
                    obs[i] = smb::Smb::feature::MARIO;
                    return;
                }

                dx += this->mario_xy[0];

                for(size_t e = 0; e < this->enemies_xy.size(); e += 2){
                    if(std::abs(this->enemies_xy[e] - dx) <= 8 && std::abs(this->enemies_xy[e + 1] - y) <= 8){
                        obs[i] = smb::Smb::feature::ENEMY;
                        return;
                    }
                }

                obs[i] = this->get_tile_t(dx, y) ? smb::Smb::feature::SAFE : smb::Smb::feature::EMPTY;
            }(x);

            i++;
        }
    }
}

void smb::Smb::set_mario()
{
    this->mario_xy[0] = this->read_cpu(0x6D) * 0x100 + this->read_cpu(0x86);
    this->mario_xy[1] = this->read_cpu(0x03B8) + 16;
}

void smb::Smb::set_enemies()
{
    this->enemies_xy.clear();
    for(int i = 0; i < 5; i++){
        if(this->read_cpu(0xF + i)){
            enemies_xy.push_back((this->read_cpu(0x6E + i) * 0x100) + this->read_cpu(0x87 + i));
            enemies_xy.push_back(this->read_cpu(0xCF + i) + 24);
        }
    }
}

bool smb::Smb::get_tile_t(int x, int y) const
{
    x += 8;
    y -= 16;

    int page = (x / 256) % 2;
    x = (x % 256) / 16;
    y = (y - 32) / 16;

    if(y >= 13 || y < 0){
        return false;
    }
    return this->read_cpu(0x500 + (page * 13 * 16) + (y * 16) + x);
}
