#include "Enemy.hpp"

Enemy::Enemy(int xPos, int yPos):Entity(xPos, yPos) {}
Enemy::~Enemy() {}
//draw unicode hexagon
void Enemy::draw() {
    std::cout << "\u2B22 ";
}