#include "Enemy.hpp"

Enemy::Enemy(int xPos, int yPos):Entity(xPos, yPos) {}
Enemy::~Enemy() {}
void Enemy::draw() {
    std::cout << "\u23FA ";
}