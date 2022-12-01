#include "env/env/smb.hpp"

smb::Smb::Smb(size_t obs_n)
{
    this->cols = std::max(std::min(this->max_cols, this->cols), 1);
    this->rows = std::max(std::min(this->max_rows, static_cast<int>(obs_n) / this->cols), 1);

    this->cols_l = std::max(std::min(this->cols, this->cols_l), 0);
    this->cols_r = std::max(std::min(this->cols, this->cols - this->cols_l), 1);

    std::cout << "cols: " << this->cols << "\n";
    std::cout << "rows: " << this->rows << "\n";
    std::cout << "cols_l: " << this->cols_l << "\n";
    std::cout << "cols_r: " << this->cols_r << "\n";
}

void smb::Smb::obs_func(std::array<float, CONF::INPUTS>& obs) const
{
    int mario_x, mario_y;
    this->get_loc(mario_x, mario_y);

    size_t i = 0;
    for(int dy=((15-this->rows)*16); dy<(15*16); dy+=16){
        for(int dx=(-this->cols_l*16); dx<(this->cols_r*16); dx+=16){
            obs[i] = (this->get_tile(mario_x + dx, dy)) ?
                     smb::Smb::feature::SAFE : smb::Smb::feature::EMPTY;

            i++;
        }
    }

    // obs[smb::Smb::to1D(mario_x, mario_y)] = smb::Smb::MARIO;
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
    x = (x % 256) / 16;
    y = (y - 32) / 16;

    if(y >= 13 || y < 0){
        return false;
    }
    return this->read_cpu(0x500 + (page * 13 * 16) + (y * 16) + x);
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