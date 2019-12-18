#include "Entity.hpp"

Entity::Entity() {}
//the constructor that is used for enemies
//random hp and strength
Entity::Entity(int xPos, int yPos) {
    x = xPos;
    y = yPos;
    hp = rand() % 50 + 1;
    strength = rand() % 10 + 1;
    alive = true;
}
//the constructor that is used for player
Entity::Entity(int xPos, int yPos, int pHp, int pStr) {
    x = xPos;
    y = yPos;
    hp = pHp;
    strength = pStr;
    alive = true;
}
Entity::~Entity() {}
//setters
void Entity::setX(int amount) {
    x = amount;
}
void Entity::setY(int amount) {
    y = amount;
}
void Entity::setHP(int amount) {
    hp = amount;
    if(hp <= 0)
        alive = false;
}
//getters
int Entity::getX() {
    return x;
}
int Entity::getY() {
    return y;
}
int Entity::getHP() {
    return hp;
}
int Entity::getStrength() {
    return strength;
}
bool Entity::isAlive() {
    return alive;
}