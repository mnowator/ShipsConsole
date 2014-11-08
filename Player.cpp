#include "Player.h"


Player::Player(std::string name) : name(name)
{
}


Player::~Player()
{
}

SHIP_STATE Player::getShot(Position pos)
{
	return sea.getShot(pos);
}

void Player::removeLastShip()
{
	sea.deleteLastShip();
}

bool Player::setShipElement(SHIP_TYPE st,Position pos)
{
	bool result = sea.setShipElement(st, pos);
	sea.refreshShips();

	return result;
}

bool Player::doShot(Position pos)
{
	return sea.doShot(pos);
}

bool Player::areShips() const
{
	return sea.areShips();
}

void Player::markHited(Position pos)
{
	sea.markHited(pos);
}

std::string Player::displayMaps() const
{
	return sea.displaySeas();
}

std::string Player::getName() const
{
	return name;
}

