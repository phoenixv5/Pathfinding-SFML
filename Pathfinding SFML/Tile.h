#pragma once
#include "IEntity.h"

class Tile :
	public IEntity
{
	bool isBlocked;

	bool hasStar;
	bool hasShip;
	bool hasStarChaser;
	bool hasTradePost;
public:
	Tile(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~Tile();
	void setBlockedStatus(bool status);
	bool getBlockedStatus();
};

