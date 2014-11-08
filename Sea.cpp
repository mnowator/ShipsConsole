#include "Sea.h"

#include <algorithm>

Sea::Sea() : MAP_SIZE(10)
{
	for (unsigned i = 0; i < MAP_SIZE; ++i)
	{
		mineArea.push_back(std::vector< char >(MAP_SIZE));
		std::fill(std::begin(mineArea.back()), std::end(mineArea.back()), ' ');

		opponentArea.push_back(std::vector< char >(MAP_SIZE));
		std::fill(std::begin(opponentArea.back()), std::end(opponentArea.back()), ' ');
	}
}


Sea::~Sea()
{
}

void Sea::deleteLastShip()
{
	if (!ships.empty()) ships.pop_back();
	refreshShips();
}

void Sea::refreshShips()
{
	for (auto &row : mineArea)
	{
		for (auto &field : row)
		{
			field = ' ';
		}
	}

	rewriteShips2map();
}

void Sea::markHited(Position pos)
{
	opponentArea[pos.posY][pos.posX] = 'X';
}

bool Sea::setShipElement(SHIP_TYPE st, Position pos)
{
	static bool newShip = true;
	bool neightborhoodCondition = false;

	if (mineArea[pos.posY][pos.posX] == ' ') // check is pos possible
	{
		int magicIndexes[] = { -1, 0, 1 };

		// check surounding places
		for (int i : magicIndexes) // y coordinate
		{
			for (int j : magicIndexes) // x coordinate
			{
				if (pos.posY+i>= 0 && pos.posX+j>=0 && pos.posY+i<=MAP_SIZE-1 && pos.posX+j<=MAP_SIZE-1)
				{
					// is field not free ? 
					if (mineArea[pos.posY + i][pos.posX + j] != ' ' ) // its not empty
					{
						if (!newShip) // for new ships we dont have to continue checking
						{
							// is it part of ship ?
							if (ships.back().belong(Position(pos.posX+j,pos.posY+i))) // its part of ship
							{


								// if statement goes good with all cases i can asume that surounding is ok
								// but also i have to check neightborhood condition
								// i can do it by checking if coordinates are in neightborhood position

								if ((i == -1 && j == 0) || // top
									(i == 0 && j == -1) || // left
									(i == 0 && j == 1) || // right
									(i == 1 && j == 0) // bottom
									)
								{
									neightborhoodCondition = true;
								}
							}
							else return false; // its not free and its not a part of ship
						}
						else return false; // cuz ship haavnt free surounding and he is new
					}
				}
			}
		}
		// finaly

		// it was new ship ?
		if (newShip)
		{
			std::vector<Position> vp;
			vp.push_back(pos);
			ships.push_back(Ship(vp, st));
			newShip = false;
		}
		else if ( neightborhoodCondition ) // otherwise, i have to check neightborhood condition
		{
			ships.back().addElement(pos);
		}
		else return false; // if its not new ship and neightborhood contition its not satisfy, then gtfo 

		//check if it's not last element, cuz then we have to prepare method to new ship
		if (ships.back().getNumElements() == static_cast<int>(st) -48) // -48 cuz its char
			newShip = true;

		return true;
	}
	else return false;
}

void Sea::rewriteShips2map()
{
	for (auto ship = std::cbegin(ships); ship != std::cend(ships); ++ship)
	{
		for (auto element = std::cbegin((*ship).getElements()); element != std::cend((*ship).getElements()); ++element)
		{
			if ((*element).second == GOOD )
				mineArea[(*element).first.posY][(*element).first.posX] = static_cast<char>((*ship).getShipType());
			else mineArea[(*element).first.posY][(*element).first.posX] = static_cast<char>((*element).second);
		}
	}
}

std::string const Sea::displaySeas() const
{
	std::string letters("ABCDEFGHIJ");
	std::string digits("0123456789");
	std::string output;

	output += ' ';

	for (char letter : letters)
		output += letter;

	output += "  ";

	for (char letter : letters)
		output += letter;

	output += '\n';

	for (unsigned i = 0; i < MAP_SIZE; ++i)
	{
		output += digits[i];

		std::for_each(std::cbegin(mineArea[i]), std::cend(mineArea[i]), [&](char field){output += field; });

		output += ' ';
		output += digits[i];

		std::for_each(std::cbegin(opponentArea[i]), std::cend(opponentArea[i]), [&](char field){output += field; });

		output += '\n';
	}

	output += '\n';

	return output;
}

bool Sea::doShot(Position pos)
{
	if (opponentArea[pos.posY][pos.posX] == ' ')
	{
		opponentArea[pos.posY][pos.posX] = '*';
		return true;
	}
	else return false;
}

SHIP_STATE Sea::getShot(Position pos)
{	
	for (auto ship = std::begin(ships); ship < std::end(ships); ++ship) // check if a ship was hit
	{
		auto result = (*ship).shot(pos);

		if (result == SUNKEN)
		{
			mineArea[pos.posY][pos.posX] = '&';
			ships.erase(ship);
			return SUNKEN;
		}
		else if (result == HITED)
		{
			mineArea[pos.posY][pos.posX] = '&';
			rewriteShips2map();
			return HITED;
		}
	}

	mineArea[pos.posY][pos.posX] = '*';
	return MISSED;
}

bool Sea::areShips() const 
{
	return !ships.empty();
}
