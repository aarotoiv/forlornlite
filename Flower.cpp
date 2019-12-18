#include "Flower.hpp"

Flower::Flower(int xPos, int yPos) {
    x = xPos;
    y = yPos;
}
Flower::~Flower() {}
//draw unicode flower
void Flower::draw() {
    std::cout << "\u2698 "; 
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