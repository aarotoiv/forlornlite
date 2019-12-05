#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>
#include <cmath>
#include <algorithm>


class Map {
    public:
        Map(Player *thePlayer);
        ~Map();
        void draw();
        void drawLog(int line);
        void updateLog(std::string text);
        void create();
        int getMaxX();
        int getMaxY();
        void moveEnemies();
        void checkCollision();
        void handleFight(int enemyIndex);

        void enemyDebug();
        
    private:
        static const int X_SIZE = 20;
        static const int Y_SIZE = 20;
        std::vector<Enemy> enemies;
        int coords[X_SIZE][Y_SIZE];
        Player *player;
        static const int LOGCAP = 20;
        std::string logs[LOGCAP]; 
};

#endif