#ifndef Enemy_hpp
#define Enemy_hpp

#include <iostream>

#include "Entity.hpp"

class Enemy : public Entity {
    public:
        Enemy(int x, int y);
        ~Enemy();
        void draw();
        
};

#endif