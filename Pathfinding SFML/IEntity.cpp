#include "stdafx.h"
#include "IEntity.h"
#include "Config.h"

IEntity::IEntity(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2)
{
	sprite[0] = sprite1;
	sprite[0].setScale(Config::TILE_SCALE,Config::TILE_SCALE);
	sprite[1] = sprite2;
	sprite[1].setScale(Config::TILE_SCALE, Config::TILE_SCALE);

	SetSprite(0);
	SetPos(x, y);
}


IEntity::~IEntity()
{
}

Index IEntity::GetIndex()
{
	return index;
}

sf::Sprite IEntity::GetSprite()
{
	return sprite[currentSprite];
}

void IEntity::SetSprite(int n)
{
	if (n >= 0 && n < (sizeof(sprite) / sizeof(sprite[0])) )
	{//Because c-arrays
		currentSprite = n;
	}
}

void IEntity::SetPos(int x, int y)
{
	index = Index(x, y);
	sprite[0].setPosition(x*Config::TILE_SIZE*Config::TILE_SCALE, y*Config::TILE_SIZE*Config::TILE_SCALE);
	sprite[1].setPosition(x*Config::TILE_SIZE*Config::TILE_SCALE, y*Config::TILE_SIZE*Config::TILE_SCALE);
}
