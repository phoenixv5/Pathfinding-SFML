#pragma once
#include "IEntity.h"
class TradingPost :
	public IEntity
{
public:
	TradingPost(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~TradingPost();
};

