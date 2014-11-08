#pragma once
#pragma once


class Position
{
public:
	unsigned posX;
	unsigned posY;

	bool operator == (Position const&) const;

	Position( unsigned x, unsigned y );
	Position(Position const&);
	Position();
	Position& operator=(Position const& pos);
	~Position();
};

