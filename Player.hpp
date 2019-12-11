#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Entity.hpp"

class Player : public Entity {
    public:
        Player();
        ~Player();
        int getStamina();
        void drawPlayer();
        void drawStats();
        void checkBounds(int maxX, int maxY);
        void applyEffect(std::string effect, int value);
        bool incrementExp(int val);
    private:
        int stamina;
        int exp;
        int level;
};

#endif