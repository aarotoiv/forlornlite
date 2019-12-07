#include "Map.hpp"
#include "util.h"

Map::Map(Player *thePlayer) {
    player = thePlayer;
    stage = 1;
    std::fill_n(logs, LOGCAP, "");
    create();
}
Map::~Map() {

}
void Map::draw() {
    std::cout << "STAGE " << stage << std::endl;
    for(int i = 0; i<X_SIZE; i++) {
        for(int j = 0; j<Y_SIZE; j++) {
            if(i == player->getY() && j == player->getX()) 
                player->drawPlayer();
            else if(i == gateY && j == gateX) {
                std::cout << "\u22D2 ";
            }
            else {
                bool entityMatch = false;
                //TODO REFACTOR THIS
                for(int k = 0; k<enemies.size(); k++) {
                    if(i == enemies[k].getY() && j == enemies[k].getX()) {
                        enemies[k].draw();
                        entityMatch = true;
                    }
                }
                if(!entityMatch) {
                    std::cout << ". ";
                }
            }
            
           
            
        }
        drawLog(i);
        std::cout << "\n";
    }
}
void Map::drawLog(int lineNumber) {
    std::cout << "\t" << logs[lineNumber];
}
void Map::create() {
    gateX = rand() % 19;
    gateY = rand() % 19;
    
    enemies.clear();

    for(int i = 0; i<X_SIZE; i++) {
        for(int j = 0; j<Y_SIZE; j++) {
            if(rand() % 100 > 90 && (i < player->getX() - 2 || i > player->getX() + 2) && (j < player->getY() - 2 || j > player->getY() + 2) && i != gateY && j != gateX)
                enemies.push_back(* new Enemy(i, j));
            coords[i][j] = 0;
        }
    } 
}

int Map::getMaxX() {
    return X_SIZE;
}
int Map::getMaxY() {
    return Y_SIZE;
}
int Map::getGateX() {
    return gateX;
}
int Map::getGateY() {
    return gateY;
}

void Map::moveEnemies() {
    for(int i = 0; i < enemies.size(); i++) {
        int playerDistanceX = plusMinusOne(player->getX() - enemies[i].getX());
        int playerDistanceY = plusMinusOne(player->getY() - enemies[i].getY());
        bool canMoveX = true;
        bool canMoveY = true;   
        for(int j = 0; j < enemies.size(); j++) {
            if(enemies[j].getX() == enemies[i].getX() + playerDistanceX && i != j && enemies[i].getY() == enemies[j].getY()) {
                canMoveX = false;
            }
            if(enemies[j].getY() == enemies[i].getY() + playerDistanceY && i != j && enemies[i].getX() == enemies[j].getX()) {
                canMoveY = false;
            }

        }
        if(enemies[i].getX() + playerDistanceX == gateX && enemies[i].getY() == gateY) {
            canMoveX = false;
        }
        if(enemies[i].getY() + playerDistanceY == gateY && enemies[i].getX() == gateX) {
            canMoveY = false;
        }
        if(rand() % 100 > 90) {
            int random = rand() % 100;
            if(random > 50 && canMoveX) {
                enemies[i].setX(enemies[i].getX() + playerDistanceX);
            } else if(canMoveY) {
                    enemies[i].setY(enemies[i].getY() + playerDistanceY);
            }
        }
        
    }
}

void Map::updateLog(std::string text) {
    for(int i = 0; i<LOGCAP; i++) {
        if(i < LOGCAP - 1) 
            logs[i] = logs[i + 1];
        else 
            logs[LOGCAP - 1] = text;
    }
}

void Map::checkCollision() {
    for(int i = 0; i < enemies.size(); i++) {
        if(enemies[i].getX() == player->getX() && enemies[i].getY() == player->getY()) {
            handleFight(i);
        }
    }
    if(player->getX() == gateX && player->getY() == gateY) {
        changeStage(stage + 1);
    }
}

void Map::handleFight(int enemyIndex) {
    int originalHP = player->getHP();
    while(enemies[enemyIndex].getHP() > 0 && player->isAlive()) {
        int newPlayerHP = player->getHP() - enemies[enemyIndex].getStrength() * (rand() % 5 * 0.1);
        int newEnemyHP = enemies[enemyIndex].getHP() - player->getStrength() * (rand() % 5 * 0.2);
        player->setHP(newPlayerHP);
        enemies[enemyIndex].setHP(newEnemyHP);
    }   
    if(enemies[enemyIndex].isAlive() || !player->isAlive()) {
        updateLog("You died.");
    } else {
        enemies.erase(enemies.begin() + enemyIndex);
        updateLog("Beat enemy. Lost " + std::to_string(originalHP - player->getHP()) + "HP in action.");
    }
}

void Map::enemyDebug() {
    for(int i = 0; i<enemies.size(); i++) {
        std::cout << i << ": " << enemies[i].getHP() << " " << enemies[i].getStrength() << std::endl;
    }
}

void Map::changeStage(int stageNumber) {
    updateLog("Moving to stage number " + std::to_string(stageNumber) + ".");
    stage = stageNumber;
    create();
}