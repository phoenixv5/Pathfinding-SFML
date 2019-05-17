#pragma once
#include "IEntity.h"
class Spaceship :
	public IEntity
{
public:
	Spaceship(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~Spaceship();
};

