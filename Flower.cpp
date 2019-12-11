#include "Flower.hpp"

Flower::Flower(int xPos, int yPos) {
    x = xPos;
    y = yPos;
}
Flower::~Flower() {}
void Flower::draw() {
    std::cout << "\u2698 "; 
}
int Flower::getX() {
    return x;
}
int Flower::getY() {
    return y;
}
std::string Flower::getEffect() {
    return "hp";
}
int Flower::getEffectValue() {
    return 10;
}