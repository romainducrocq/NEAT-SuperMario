#ifndef _ENV_SMB_HPP
#define _ENV_SMB_HPP

#include <memory>

#include <array>

#include "env/conf.hpp"

namespace View { class Renderer; }

namespace smb
{
    /*
    const float EMPTY = 0.f;
    const float SAFE = 1.f;
    const float ENEMY = -1.f;

    const size_t SPRITE = 16;
    const size_t HEIGHT = 10;
    const size_t WIDTH = 7;

    enum ram{
    };
     */

    /*
    enum Enemy{
        GREEN_KOOPA1 = 0X00,
        RED_KOOPA1 = 0X01,
        BUZZY_BEETLE = 0X02,
        RED_KOOPA2 = 0X03,
        GREEN_KOOPA2 = 0X04,
        HAMMER_BROTHER = 0X05,
        GOOMBA = 0X06,
        BLOOPER = 0X07,
        BULLET_BILL = 0X08,
        GREEN_KOOPA_PARATROOPA = 0X09,
        GREY_CHEEP_CHEEP = 0X0A,
        RED_CHEEP_CHEEP = 0X0B,
        POBODOO = 0X0C,
        PIRANHA_PLANT = 0X0D,
        GREEN_PARATROOPA_JUMP = 0X0E,
        BOWSER_FLAME1 = 0X10,
        LAKITU = 0X11,
        SPINY_EGG = 0X12,
        FLY_CHEEP_CHEEP = 0X14,
        BOWSER_FLAME2 = 0X15,
        GENERIC_ENEMY = 0XFF
    };

    enum StaticTile{
        EMPTY = 0X00,
        FAKE = 0X01,
        GROUND = 0X54,
        TOP_PIPE1 = 0X12,
        TOP_PIPE2 = 0X13,
        BOTTOM_PIPE1 = 0X14,
        BOTTOM_PIPE2 = 0X15,
        FLAGPOLE_TOP =  0X24,
        FLAGPOLE = 0X25,
        COIN_BLOCK1 = 0XC0,
        COIN_BLOCK2 = 0XC1 ,
        COIN = 0XC2,
        BREAKABLE_BLOCK = 0X51,
        GENERIC_STATIC_TILE = 0XFF
    };

    enum DynamicTile{
        MARIO = 0XAA,
        STATIC_LIFT1 = 0X24,
        STATIC_LIFT2 = 0X25,
        VERTICAL_LIFT1 = 0X26,
        VERTICAL_LIFT2 = 0X27,
        HORIZONTAL_LIFT = 0X28,
        FALLING_STATIC_LIFT = 0X29,
        HORIZONTAL_MOVING_LIFT=  0X2A,
        LIFT1 = 0X2B,
        LIFT2 = 0X2C,
        VINE = 0X2F,
        FLAGPOLE2 = 0X30,
        START_FLAG = 0X31,
        JUMP_SPRING = 0X32,
        WARPZONE = 0X34,
        SPRING1 = 0X67,
        SPRING2 = 0X68,
        GENERIC_DYNAMIC_TILE = 0XFF
    };

    enum Location{
        ENEMY_DRAWN = 0X0F,
        ENEMY_TYPE = 0X16,
        ENEMY_X_POSITION_IN_LEVEL = 0X6E,
        ENEMY_X_POSITION_ON_SCREEN = 0X87,
        ENEMY_Y_POSITION_ON_SCREEN = 0XCF,
        PLAYER_X_POSTION_IN_LEVEL = 0X06D,
        PLAYER_X_POSITION_ON_SCREEN = 0X086,
        PLAYER_X_POSITION_SCREEN_OFFSET = 0X3AD,
        PLAYER_Y_POSITION_SCREEN_OFFSET = 0X3B8,
        ENEMY_X_POSITION_SCREEN_OFFSET = 0X3AE,
        PLAYER_Y_POS_ON_SCREEN = 0XCE,
        PLAYER_VERTICAL_SCREEN_POSITION = 0XB5
    };
    */

    /*
    struct Vec2
    {
        size_t x;
        size_t y;

        Vec2()
            : x(0), y(0) {}

        Vec2(size_t x, size_t y)
            : x(x), y(y) {}

        static inline size_t to1D(smb::Vec2 v, size_t w=smb::WIDTH){
            return v.x + v.y * w;
        }

        static inline size_t to1D(size_t x, size_t y, size_t w=smb::WIDTH){
            return x + y * w;
        }
    };
     */

    class Smb
    {
        private:
            friend class View::Renderer;

        private:
            const float SAFE = 1.f;
            const float EMPTY = 0.f;
            const float ENEMY = -1.f;
            // const float MARIO = ??;

            const size_t COLS = 10;
            const size_t ROWS = 10;
            const size_t SPRITE = 16;

            enum ram{
            };

        private:
        /*
            size_t max_num_enemies = 5;
            size_t page_size = 256;
            size_t num_blocks = 8;
            size_t num_tiles = 416; // 0x69f - 0x500 + 1,
            size_t num_screen_pages = 2;
            size_t total_ram = 2048;
            smb::Vec2 resolution = smb::Vec2(256, 240);
    */

        private:
            inline size_t to1D(size_t x, size_t y) const
            {
                return x + y * this->COLS;
            }

        public:
            Smb() = default;

            void obs_func(std::array<float, CONF::INPUTS>& obs) const;
    };
}

#endif