#pragma once
#include "IEntity.h"
class FallenStar :
	public IEntity
{
public:
	FallenStar(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~FallenStar();
};

