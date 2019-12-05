#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Entity.hpp"

class Player : public Entity {
    public:
        Player();
        ~Player();
        void drawPlayer();
        void drawStats();
        void checkBounds(int maxX, int maxY);
    private:
        int stamina;
};

#endif