#include "stdafx.h"
#include "StartButton.h"


StartButton::StartButton(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2) : IEntity(x, y, sprite1, sprite2)
{
	sprite[0].setScale(1, 1);
	sprite[1].setScale(1, 1);
}

StartButton::~StartButton()
{
}
