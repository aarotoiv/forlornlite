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
        int getGateX();
        int getGateY();
        void moveEnemies();
        void checkCollision();
        void handleFight(int enemyIndex);

        void enemyDebug();
        
    private:
        void changeStage(int stageNumber);

        static const int X_SIZE = 20;
        static const int Y_SIZE = 20;
        static const int LOGCAP = 20;
        Player *player;
        std::vector<Enemy> enemies;
        std::string logs[LOGCAP]; 
        int coords[X_SIZE][Y_SIZE];
        int stage;
        int gateX;
        int gateY;
};

#endif