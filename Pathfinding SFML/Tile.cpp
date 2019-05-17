#include "stdafx.h"
#include "Tile.h"


Tile::Tile(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2) : IEntity(x,y,sprite1,sprite2)
{
	isBlocked = false;
	hasShip = hasStar = hasStarChaser = hasTradePost = false;
}


Tile::~Tile()
{
}

void Tile::setBlockedStatus(bool blockedStatus)
{
	isBlocked = blockedStatus;
	if (blockedStatus)
	{
		SetSprite(1);
	}
	else
	{
		SetSprite(0);
	}
}

bool Tile::getBlockedStatus()
{
	return isBlocked;
}
