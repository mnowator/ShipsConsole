#include "Ship.h"

#include <algorithm>

Ship::Ship(std::vector< Position > const& elementsPos, SHIP_TYPE shipType) : shipType( shipType )
{
	for (auto position = std::cbegin(elementsPos); position < std::cend(elementsPos); ++position)
	{
		elements.push_back(std::make_pair< Position, ELEMENT_STATE >(Position(*position), GOOD));
	}
}


Ship::~Ship()
{
}

void Ship::addElement(Position pos)
{
	elements.push_back(std::make_pair< Position, ELEMENT_STATE >(Position(pos),GOOD));
}

unsigned Ship::getNumElements() const
{
	return elements.size();
}

bool Ship::belong(Position pos) const
{
	return std::any_of(std::cbegin(elements), std::cend(elements), [&](std::pair< Position, ELEMENT_STATE > sp){ return sp.first == pos; });
}

SHIP_TYPE Ship::getShipType() const
{
	return shipType;
}


SHIP_STATE Ship::shot(Position shutPos)
// function assuming, that shuting position cannot by repeated
{
	// return iterator to element, when shuted position is in ship elements
	auto element = std::find_if(std::begin(elements), std::end(elements), [&](std::pair< Position, ELEMENT_STATE > p){return p.first == shutPos; });

	if (element != elements.end())
	{
		(*element).second = BROKEN;
		elements.erase(element);

		if (elements.empty())
			return SUNKEN;
		else return HITED;
	}
	else return MISSED;
}

std::vector< std::pair< Position, ELEMENT_STATE > > const& Ship::getElements() const
{
	return elements;
}