#ifndef _ENV_RAM_HPP
#define _ENV_RAM_HPP

namespace smb
{
    class Ram
    {
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
            FLAGPOLE = 0X30,
            START_FLAG = 0X31,
            JUMP_SPRING = 0X32,
            WARPZONE = 0X34,
            SPRING1 = 0X67,
            SPRING2 = 0X68,
            GENERIC_DYNAMIC_TILE = 0XFF
        };

        private:
            Ram() = default;

        public:
            Ram(const Ram& other) = delete;
            Ram operator=(const Ram& other) = delete;

            static Ram& RAM()
            {
                static Ram singleton;
                return singleton;
            }
    };

}

#endif