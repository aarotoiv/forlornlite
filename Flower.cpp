#include "Flower.hpp"

Flower::Flower(int xPos, int yPos) {
	x = xPos;
	y = yPos;
}
Flower::~Flower() {}
//draw unicode flower or F on windows
void Flower::draw() {
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		std::wcout << "F ";
	#else 
		std::cout << "\u2698 ";
	#endif
}
//getters
int Flower::getX() {
	return x;
}
int Flower::getY() {
	return y;
}
//effect is always +10 hp
//this is created like it is because it makes adding more effects much easier
std::string Flower::getEffect() {
	return "hp";
}
int Flower::getEffectValue() {
	return 10;
}