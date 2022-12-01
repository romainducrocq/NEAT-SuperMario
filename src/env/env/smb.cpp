#include "env/env/smb.hpp"

smb::Smb::Smb(size_t /*obs_n*/)
{
    /*
    this->cols = std::min(static_cast<size_t>(15), this->cols);
    this->rows = obs_n / this->cols;

    this->cols_l = std::min(this->cols, this->cols_l);
    this->cols_r = this->cols - this->cols_l;
     */
}

void smb::Smb::obs_func(std::array<float, CONF::INPUTS>& obs) const
{
    int mario_x, mario_y;
    this->get_loc(mario_x, mario_y);

    size_t i = 0;
    for(int dy=(-6*16); dy<=(6*16); dy+=16){
        for(int dx=(-6*16); dx<=(6*16); dx+=16){
            obs[i] = (mario_y + dy < 0x1B0 && this->get_tile(mario_x + dx, mario_y + dy)) ?
                     smb::Smb::feature::SAFE : smb::Smb::feature::EMPTY;

            i++;
        }
    }
}

void smb::Smb::obs_mario(std::array<float, CONF::INPUTS>& /*obs*/) const
{
    // size_t x = (this->read_cpu(smb::Smb::ram::PLAYER_X_POSITION_SCREEN_OFFSET) + this->sprite) / this->max_cols;
    // size_t y = (this->read_cpu(smb::Smb::ram::PLAYER_Y_POSITION_SCREEN_OFFSET) + this->sprite) / this->max_rows;

    // x = std::min(std::max(x, this->cols_l), this->max_cols - this->cols_r);

    // std::cout << "x: " << x << ", y: " << y << "\n";
}

void smb::Smb::obs_tiles(std::array<float, CONF::INPUTS>& /*obs*/) const
{
}

void smb::Smb::obs_enemies(std::array<float, CONF::INPUTS>& /*obs*/) const
{
}

void smb::Smb::get_loc(int& x, int& y) const
{
    x = this->read_cpu(0x6D) * 0x100 + this->read_cpu(0x86);
    y = this->read_cpu(0x03B8) + 16;
}

bool smb::Smb::get_tile(int x, int y) const
{
    x += 8;
    y -= 16;

    int page = (x / 256) % 2;

    int sub_x = (x % 256) / 16;
    int sub_y = (y - 32) / 16;
    int addr = 0x500 + (page * 13 * 16) + (sub_y * 16) + sub_x;

    if(sub_y >= 13 || sub_y < 0){
        return false;
    }

    return this->read_cpu(addr);
}

//smb::Smb::feature smb::Smb::get_tile(size_t /*x*/, size_t /*y*/) const
//{
//    return smb::Smb::feature::EMPTY;
//}

void smb::Smb::get_mario_loc_displ(size_t& x, size_t& y) const
{
    x = this->read_cpu(smb::Smb::ram::PLAYER_X_POSITION_SCREEN_OFFSET);
    y = this->read_cpu(smb::Smb::ram::PLAYER_Y_POS_ON_SCREEN) *
            (this->read_cpu(smb::Smb::ram::PLAYER_VERTICAL_SCREEN_POSITION) + this->sprite);
}

void smb::Smb::get_mario_loc_level(size_t& /*x*/, size_t& /*y*/) const
{
}