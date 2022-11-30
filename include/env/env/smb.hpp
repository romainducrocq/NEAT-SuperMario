#ifndef _ENV_SMB_HPP
#define _ENV_SMB_HPP

#include <array>

#include "env/env/ram.hpp"

namespace smb
{
    class Smb
    {
        size_t max_num_enemies = 5;
        size_t page_size = 256;
        size_t num_blocks = 8;
        size_t num_tiles = 416; // 0x69f - 0x500 + 1,
        size_t num_screen_pages = 2;
        size_t total_ram = 2048;
        Vec2<size_t> resolution = Vec2<size_t>(256, 240);

        private:
            std::array<size_t, 5> enemies = { 0 };

        private:
            Smb() = default;

        public:
            void init();

            void obs_func();

        public:
            Smb(const Smb& other) = delete;
            Smb operator=(const Smb& other) = delete;

            static Smb& SMB()
            {
                static Smb singleton;
                return singleton;
            }
    };
}

#endif