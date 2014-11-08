#include "Position.h"


Position::Position(unsigned x, unsigned y) : posX(x), posY(y)
{
}

Position::Position(Position const& pos)
{
	posX = pos.posX;
	posY = pos.posY;
}

Position& Position::operator=(Position const& pos)
{
	posX = pos.posX;
	posY = pos.posY;

	return *this;
}

Position::Position()
{

}


Position::~Position()
{
}

bool Position::operator== (Position const& pos) const
{
	return (posX == pos.posX && posY == pos.posY);
}
