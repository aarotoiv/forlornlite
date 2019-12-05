#include "Player.hpp"

Player::Player() : Entity(5, 5, 100, 10) {
    stamina = 100;
}
Player::~Player() {}
void Player::drawPlayer() {
    std::cout << "\u25A0 ";
}   
void Player::drawStats() {
    std::cout << "HP\tSTAMINA\n" << Entity::getHP() << "\t" << stamina << std::endl; 
}
void Player::checkBounds(int maxX, int maxY) {
    if(Entity::getX() < 0) 
        Entity::setX(0);
    if(Entity::getX() > maxX - 1)
        Entity::setX(maxX - 1);
    if(Entity::getY() < 0)
        Entity::setY(0);
    if(Entity::getY() > maxY - 1)
        Entity::setY(maxY - 1);
}
