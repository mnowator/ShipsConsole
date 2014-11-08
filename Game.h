#pragma once

#include "Player.h"
#include "AIPlayer.h"

#include <random>

class WrongPosition{
public:
	WrongPosition()
	{
	}
};

enum GAME_STATE { IN_PROGRES, IN_MENU_1, IN_MENU_2, IN_SHIP_PREPARING, IN_QUIT };
enum TURN { PLAYER1, PLAYER2 };

class Game
{
private:
	std::vector< unsigned > maxNumberOfShips;

	SHIP_TYPE curentlySetingShip;
	unsigned numElementsOfCurrentShip;
	unsigned numOfCurentTypeShip;

	Player* player1;
	Player* player2;

	GAME_STATE gs;
	TURN turn;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dis0to9;
	std::uniform_int_distribution<> dis0to1;

	void setUpShipsAuto( Player*& );
	void menu1();
	void shipPreparing();
	void game();
	Position signs2position(char, char) const;
	std::tuple< char, char > position2signs(Position) const;

public:

	void loop();

	Game();
	~Game();
};

