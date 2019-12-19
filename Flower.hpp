#ifndef Flower_hpp
#define Flower_hpp

#include <iostream>

//flower class
class Flower {
public:
	Flower(int xPos, int yPos);
	~Flower();
	void draw();
	int getX();
	int getY();
	std::string getEffect();
	int getEffectValue();
private:
	int x;
	int y;
};
#endif