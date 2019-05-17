#pragma once
#include "IEntity.h"

class StartButton :	public IEntity
{
public:
	StartButton(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~StartButton();
};

