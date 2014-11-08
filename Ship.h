#pragma once

#include <vector>
#include <utility>

#include "Position.h"

enum SHIP_TYPE { SINGLE = '1', DOUBLE = '2', TRIPLE = '3', QUADRO = '4', PENTO = '5' };
enum ELEMENT_STATE { GOOD, BROKEN='&' };
enum SHIP_STATE { HITED='^', SUNKEN='%', MISSED='*' };

class Ship
{
private:
	SHIP_TYPE shipType;
	std::vector< std::pair< Position, ELEMENT_STATE > > elements;

public:
	Ship(std::vector< Position > const&, SHIP_TYPE);
	~Ship();

	void addElement(Position);
	unsigned getNumElements() const;
	bool belong(Position) const;
	SHIP_TYPE getShipType() const;
	SHIP_STATE shot( Position );
	std::vector< std::pair< Position, ELEMENT_STATE > > const& getElements() const;
};

