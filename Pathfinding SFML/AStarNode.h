#pragma once
#include "IEntity.h"

class AStarNode : public IEntity
{
	int f; //Total
	int g; //Travelled
	int h; //Remaining
	AStarNode* parent;
public:
	void setFGH(int fVal, int gVal, int hVal);
	int getFGH(char type);
	AStarNode* getParent();
	void setParent(AStarNode* parentNode);

	AStarNode(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2, AStarNode * parentNode);
	~AStarNode();
};

