#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "AStarNode.h"

typedef std::map<Index, AStarNode*> AStarNodeList;

class AStarMain
{
	bool pathFound;

	AStarNodeList openNodes;
	AStarNodeList closedNodes;
	std::vector<AStarNode*> path;

	std::vector<Index> blockedTiles;
	
	sf::Sprite openNodeSprite;
	sf::Sprite closedNodeSprite;
	
public:
	bool calculateFGH(AStarNode* node, AStarNode* end);
	void AddNearby(AStarNode* node, AStarNode* end);
	bool AddNode(AStarNode* parent, AStarNode* end, Index nodeIndex);
	bool MoveToClosed(Index nodeIndex);
	AStarNode* FindLowest();
	bool FindAStarPathRecursive(AStarNode* start, AStarNode* end);
	std::vector<AStarNode*> FindAStarPath(std::vector<Index> blocked, Index startIndex, Index endIndex);
	void reset();

	AStarMain(sf::Sprite sprite1, sf::Sprite sprite2);
	~AStarMain();
};

