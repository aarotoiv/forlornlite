#ifndef Enemy_hpp
#define Enemy_hpp

#include <iostream>

#include "Entity.hpp"

//enemy class
//inherits all the important stuff from entity class
class Enemy : public Entity {
public:
	Enemy(int x, int y);
	~Enemy();
	void draw();

};

#endif