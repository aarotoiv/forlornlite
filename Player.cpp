#include "Player.hpp"

Player::Player() : Entity(5, 5, 100, 10) {
	stamina = 100;
	level = 1;
	exp = 0;
}
Player::~Player() {}
//draw unicode rect or O on windows
void Player::drawPlayer() {
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		std::cout << "O ";
	#else 
		std::cout << "\u25A0 ";
	#endif
}
//draw player stats under the grid
void Player::drawStats() {
	std::cout << "HP\tSTAMINA\tLEVEL\tEXP\n" << Entity::getHP() << "\t" << stamina << "\t" << level << "\t" << std::to_string(exp - (level - 1) * 100) + "/100" << std::endl;
}
//check if player is attempting to get out of the set grid
void Player::checkBounds(int maxX, int maxY) {
	if (Entity::getX() < 0)
		Entity::setX(0);
	else if (Entity::getX() > maxX - 1)
		Entity::setX(maxX - 1);
	else if (Entity::getY() < 0)
		Entity::setY(0);
	else if (Entity::getY() > maxY - 1)
		Entity::setY(maxY - 1);
	//successful move, stamina can be reduced
	else
		stamina--;
}
//apply flower effect
void Player::applyEffect(std::string effect, int value) {
	if (effect == "hp") {
		Entity::setHP(Entity::getHP() + value);
	}
}
//increase exp, level up if exp >= 100, return a bool so map knows if level up happened
bool Player::incrementExp(int val) {
	exp += val;
	int levelProg = exp - (level - 1) * 100;
	if (levelProg >= 100) {
		level++;
		stamina = 100;
		return true;
	}
	return false;
}
//get stamina
int Player::getStamina() {
	return stamina;
}