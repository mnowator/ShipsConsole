#pragma once

#include <string>
#include <tuple>

#include "Ship.h"

class Sea
{
private:
	const unsigned	MAP_SIZE;

	std::vector< std::vector< char > > mineArea;
	std::vector< std::vector< char > > opponentArea;

	std::vector< Ship > ships;

	void rewriteShips2map();

public:
	Sea();
	~Sea();

	void deleteLastShip();
	void refreshShips();
	void markHited(Position);
	bool setShipElement(SHIP_TYPE, Position);
	std::string const displaySeas() const;
	bool doShot(Position);
	SHIP_STATE getShot( Position );
	bool areShips() const;
};

