#pragma once

#include <string>

#include "Sea.h"

class Player
{
private:
	std::string name;
	Sea sea;

public:

	SHIP_STATE getShot(Position pos);

	void removeLastShip();
	void markHited(Position);

	bool setShipElement(SHIP_TYPE,Position);
	bool doShot(Position);
	bool areShips() const;

	std::string displayMaps() const;
	std::string getName() const;

	Player(std::string name);
	~Player();
};

