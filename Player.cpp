#include "Player.hpp"

Player::Player() : Entity(5, 5, 100, 10) {
    stamina = 100;
    level = 1;
    exp = 0;
}
Player::~Player() {}
int Player::getStamina() {
    return stamina;
}
void Player::drawPlayer() {
    std::cout << "\u25A0 ";
}   
void Player::drawStats() {
    std::cout << "HP\tSTAMINA\tLEVEL\tEXP\n" << Entity::getHP() << "\t" << stamina << "\t" << level << "\t" << std::to_string(exp - (level-1) * 100) + "/100" << std::endl; 
}
void Player::checkBounds(int maxX, int maxY) {
    if(Entity::getX() < 0) 
        Entity::setX(0);
    else if(Entity::getX() > maxX - 1)
        Entity::setX(maxX - 1);
    else if(Entity::getY() < 0)
        Entity::setY(0);
    else if(Entity::getY() > maxY - 1)
        Entity::setY(maxY - 1);
    //successful move, stamina can be reduced
    else
        stamina--;
    
}
void Player::applyEffect(std::string effect, int value) {
    if(effect == "hp") {
        Entity::setHP(Entity::getHP() + value);
    }
}
bool Player::incrementExp(int val) {
    exp += val;
    int levelProg = exp - (level-1) * 100;
    if(levelProg > 100)  {
        level++;    
        stamina = 100;
        return true;
    }
    return false;
}
