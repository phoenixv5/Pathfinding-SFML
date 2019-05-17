#include "stdafx.h"
#include "Config.h"
#include "AStarNode.h"

void AStarNode::setFGH(int fVal, int gVal, int hVal)
{
	f = fVal;
	g = gVal;
	h = hVal;
}

int AStarNode::getFGH(char type)
{
	switch (type)
	{
	case 'f':return f;break;
	case 'g':return g;break;
	case 'h':return h;break;
	}

	return 0;
}

AStarNode * AStarNode::getParent()
{
	return parent;
}

void AStarNode::setParent(AStarNode * parentNode)
{
	parent = parentNode;
}

AStarNode::AStarNode(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2, AStarNode* parentNode) : IEntity(x, y, sprite1, sprite2)
{
	parent = parentNode;
	setFGH(0, 0, 0);
}


AStarNode::~AStarNode()
{
}
