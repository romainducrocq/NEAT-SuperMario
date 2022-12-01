#include "env/env/smb.hpp"

smb::Smb::Smb(size_t obs_n)
{
    this->rows = obs_n / this->cols;
}

void smb::Smb::obs_func(std::array<float, CONF::INPUTS>& /*obs*/) const
{
}