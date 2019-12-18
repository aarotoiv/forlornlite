#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "util.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Flower.hpp"


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

        void enemyDebug();
        
    private:
        void changeStage(int stageNumber);
        void handleEffect(int flowerIndex);
        void handleFight(int enemyIndex);

        static const int X_SIZE = 20;
        static const int Y_SIZE = 20;
        Player *player;
        std::vector<Enemy> enemies;
        std::vector<Flower> flowers;
        std::string logs[Y_SIZE]; 
        int coords[X_SIZE][Y_SIZE];
        int stage;
        int gateX;
        int gateY;
};

#endif