#include "Map.hpp"
//constructor, set the local player pointer to the current player pointer
Map::Map(Player *thePlayer) {
    player = thePlayer;
    stage = 1;
    std::fill_n(logs, Y_SIZE, "");
    create();
}

//destructor that does nothing
Map::~Map() {}

//draws the x*y grid and any entities or objects that it should
void Map::draw() {
    //stage level
    std::cout << "STAGE " << stage << std::endl;
    //loop thru x and y axis
    for(int i = 0; i<Y_SIZE; i++) {
        for(int j = 0; j<X_SIZE; j++) {
            if(i == player->getY() && j == player->getX()) 
                player->drawPlayer();
            else if(i == gateY && j == gateX) {
                std::cout << "\u22C2 ";
            }
            else {
                bool entityMatch = false;
                //TODO REFACTOR THIS
                for(int k = 0; k<enemies.size(); k++) {
                    if(i == enemies[k].getY() && j == enemies[k].getX()) {
                        enemies[k].draw();
                        entityMatch = true;
                        break;
                    }
                }
                for(int k = 0; k<flowers.size(); k++) {
                    if(i == flowers[k].getY() && j == flowers[k].getX()) {
                        flowers[k].draw();
                        entityMatch = true;
                        break;
                    }
                }
                if(!entityMatch) {
                    std::cout << "\u22C5 ";
                }
            }
            
           
            
        }
        drawLog(i);
        std::cout << "\n";
    }
}
//draw specific log line
void Map::drawLog(int lineNumber) {
    std::cout << "\t" << logs[lineNumber];
}
//initialize map
//get random gate positions, clear existing enemies and flowers
//around 1/10 chance for a block to have an enemy in it
//around 1/20 chance for a block to have a flower in it
//enemies and flowers cant spawn on top of gate, eachother or within 2 blocks of player
void Map::create() {
    gateX = rand() % (X_SIZE - 1);
    gateY = rand() % (Y_SIZE - 1);
    
    enemies.clear();
    flowers.clear();

    for(int i = 0; i<X_SIZE; i++) {
        for(int j = 0; j<Y_SIZE; j++) {
            if(rand() % 100 > 90 && (i < player->getX() - 2 || i > player->getX() + 2) && (j < player->getY() - 2 || j > player->getY() + 2) && i != gateY && j != gateX)
                enemies.push_back(* new Enemy(i, j));
            else if(rand() % 100 > 95 && (i < player->getX() - 2 || i > player->getX() + 2) && (j < player->getY() - 2 || j > player->getY() + 2) && i != gateY && j != gateX) {
                flowers.push_back(* new Flower(i, j));
            }
        }
    } 
}

//getters
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

//move enemies
//big brain ai 
//enemies always want to move TOWARDS the player
//enemies can only move 1 BLOCK at a time on either x or y axis
//enemies cant move on top of each other
//enemies cant move on top of flowers
//enemies cant move on top of gate
//higher level = higher chance of enemies moving
void Map::moveEnemies() {
    int moveChanceMod = stage + 10 > 40 ? 40 : stage + 10;
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
        for(int j = 0; j < flowers.size(); j++) {
            if(flowers[j].getX() == enemies[i].getX() + playerDistanceX && enemies[i].getY() == flowers[j].getY()) {
                canMoveX = false;
            }
            if(flowers[j].getY() == enemies[i].getY() + playerDistanceY && enemies[i].getX() == flowers[j].getX()) {
                canMoveY = false;
            }
        }
        if(rand() % 100 > 100 - moveChanceMod) {
            int random = rand() % 100;
            if(random > 50 && canMoveX) {
                enemies[i].setX(enemies[i].getX() + playerDistanceX);
            } else if(canMoveY) {
                    enemies[i].setY(enemies[i].getY() + playerDistanceY);
            }
        }
        
    }
}
//add new line of text on the logger
void Map::updateLog(std::string text) {
    for(int i = 0; i<Y_SIZE; i++) {
        if(i < Y_SIZE - 1) 
            logs[i] = logs[i + 1];
        else 
            logs[Y_SIZE - 1] = text;
    }
}

//check player collisions with gate, enemies and flowers
void Map::checkCollision() {
    for(int i = 0; i < enemies.size(); i++) {
        if(enemies[i].getX() == player->getX() && enemies[i].getY() == player->getY()) {
            handleFight(i);
        }
    }
    for(int i = 0; i < flowers.size(); i++) {
        if(flowers[i].getX() == player->getX() && flowers[i].getY() == player->getY()) {
            handleEffect(i);
        }
    }
    if(player->getX() == gateX && player->getY() == gateY) {
        changeStage(stage + 1);
    }
}

//fight to death when encountering enemy
//get player hp
//loop until either the player or the enemy is dead
//damage dealt is strength decreased by a slightly rngish modifier
//player dies -> reset happens in mainloop in main.cpp
//enemy dies -> increase player exp by enemy strength * 2
//              erase enemy, update logger with hp lost and exp gained alerts
//              if player levels up, update logger with level up alert and replenish stamina back up to default value(100)
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
        int expAmount = enemies[enemyIndex].getStrength() * 2;
        enemies.erase(enemies.begin() + enemyIndex);
        updateLog("Beat enemy. Lost " + std::to_string(originalHP - player->getHP()) + "HP in action.");
        updateLog("Gained " + std::to_string(expAmount) + " experience points!");
        if(player->incrementExp(expAmount)) {
            updateLog("Leveled up! Stamina has been replenished!");
        }
    }
}

//remove flower that the player hit
//handle effect (only 1 effect at this time (increase hp by 10))
void Map::handleEffect(int flowerIndex) {
    flowers.erase(flowers.begin() + flowerIndex);
    player->applyEffect(flowers[flowerIndex].getEffect(), flowers[flowerIndex].getEffectValue());
}

//random debugger line to just quickly output enemy hps and strengths
//not in use in prod
void Map::enemyDebug() {
    for(int i = 0; i<enemies.size(); i++) {
        std::cout << i << ": " << enemies[i].getHP() << " " << enemies[i].getStrength() << std::endl;
    }
}

//change stage and recreate map
void Map::changeStage(int stageNumber) {
    updateLog("Moving to stage number " + std::to_string(stageNumber) + ".");
    stage = stageNumber;
    create();
}