#include "Enemy.hpp"

Enemy::Enemy(int xPos, int yPos) :Entity(xPos, yPos) {}
Enemy::~Enemy() {}
//draw unicode hexagon or X on windows
void Enemy::draw() {
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		std::cout << "X ";
	#else 
		std::cout << "\u2B22 ";
	#endif
}