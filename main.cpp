
#include <iostream>
#include <cmath>
#include <time.h>

#include "Player.hpp"
#include "Map.hpp"

//init player and map
Player *player = new Player();
Map *map = new Map(player);
bool running = true;

void handleCommand(std::string command);
void reset();

//main function and mainloop
int main() {
	std::string command = "";
	while (running) {
		if (player->getHP() <= 0 || player->getStamina() <= 0)
			reset();
		//seed for rand()
		srand(time(0));
		//clears the terminal/cmd before redraw
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
			std::system("cls");
		#else 
			std::system("clear");
		#endif
		//draw map & player stats
		map->draw();
		player->drawStats();
		//map->enemyDebug();
		//get command from user, handle it
		std::cout << "Insert command: " << std::endl;
		std::cin >> command;
		handleCommand(command);
	}
	return 0;
}

//doing it the harsh way
void reset() {
	player = new Player();
	map = new Map(player);
}

//handle commands
void handleCommand(std::string command) {
	std::string action = "";
	//get only first letter and always set it to lowercase for easier comparison
	//does whatever the command tells it to eg. move
	switch (tolower(command.at(0))) {
	case 'a':
		player->setX(player->getX() - 1);
		action = "moved";
		break;
	case 'd':
		player->setX(player->getX() + 1);
		action = "moved";
		break;
	case 'w':
		player->setY(player->getY() - 1);
		action = "moved";
		break;
	case 's':
		player->setY(player->getY() + 1);
		action = "moved";
		break;
	case 'q':
		running = false;
		break;
	}
	//check player bounds if player is trying to get out of the 20x20 grid
	player->checkBounds(map->getMaxX(), map->getMaxY());
	//move enemies with sick AI
	map->moveEnemies();
	//update the log that is drawn on the right side of the grid
	map->updateLog("Player moved to X: " + std::to_string(player->getX() + 1) + " Y: " + std::to_string(player->getY() + 1));
	//check collisions between player and other entities or items
	map->checkCollision();
}
