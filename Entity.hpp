#ifndef Entity_hpp
#define Entity_hpp

#include <iostream>

//entity class
//player and enemy class inherit this classes functionalities
class Entity {
public:
	Entity();
	Entity(int xPos, int yPos);
	Entity(int xPos, int yPos, int pHp, int pStr);
	~Entity();
	void setX(int amount);
	void setY(int amount);
	void setHP(int amount);
	int getX();
	int getY();
	int getHP();
	int getStrength();
	bool isAlive();
private:
	int x;
	int y;
	int hp;
	int strength;
	bool alive;
};
#endif