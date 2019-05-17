#include "stdafx.h"
#include "AStarMain.h"
#include "Config.h"
#include <cmath>
#include <iostream>

AStarMain::AStarMain(sf::Sprite sprite1, sf::Sprite sprite2)
{
	openNodeSprite = sprite1;
	closedNodeSprite = sprite2;
	reset();
}


AStarMain::~AStarMain()
{
}

void AStarMain::reset()
{
	openNodes.clear();
	closedNodes.clear();
	path.clear();
	pathFound = false;
}


bool AStarMain::calculateFGH(AStarNode * node, AStarNode * end)
{
	int f = 0, g = 0, h = 0;
	Index nodeIndex = node->GetIndex(), endIndex = end->GetIndex();

	if (node->getParent() != nullptr)
	{
		Index parentIndex = node->getParent()->GetIndex();
		if (abs(nodeIndex.first - parentIndex.first) != 1 && abs(nodeIndex.second - parentIndex.second) != 1)
		{
			node->setFGH(0, 0, 0);
			return false;
		}

		//Travelled (g)
		if (nodeIndex.first != parentIndex.first && nodeIndex.second != parentIndex.second)
		{
			g = node->getParent()->getFGH('g') + 14;
		}
		else if (nodeIndex.first != parentIndex.first || nodeIndex.second != parentIndex.second)
		{
			g = node->getParent()->getFGH('g') + 10;
		}
		else
		{
			g = 0;
		}
	}
	else
	{
		g = 0;
	}

	//Remaining (h)
	h = (abs(nodeIndex.first - endIndex.first) + abs(nodeIndex.second - endIndex.second));
	h *= 10;

	//Total (f)
	f = g + h;

	node->setFGH(f, g, h);
	return true;
}

bool AStarMain::AddNode(AStarNode * parent, AStarNode* end, Index nodeIndex)
{
	if (nodeIndex.first >= Config::GRID_WIDTH || nodeIndex.first < 0 ||
		nodeIndex.second >= Config::GRID_HEIGHT || nodeIndex.second < 0)
	{
		return false;
	}

	for (auto it : blockedTiles)
	{
		if (it.first == nodeIndex.first && it.second == nodeIndex.second)
		{
			return false;
		}
	}

	if (closedNodes.find(nodeIndex) != closedNodes.end())
	{
		return false;
	}

	if (openNodes.find(nodeIndex) == openNodes.end())
	{
		AStarNode* temp = new AStarNode(nodeIndex.first, nodeIndex.second, openNodeSprite, closedNodeSprite, parent);
		calculateFGH(temp, end);
		openNodes.insert(std::pair<Index, AStarNode*>(nodeIndex, temp));
		return true;
	}
	else
	{
		AStarNode* openEntry = openNodes.find(nodeIndex)->second;

		int tentativeG = parent->getFGH('g');
		Index parentIndex = parent->GetIndex();

		if (nodeIndex.first != parentIndex.first && nodeIndex.second != parentIndex.second)
		{
			tentativeG += 14;
		}
		else if (nodeIndex.first != parentIndex.first || nodeIndex.second != parentIndex.second)
		{
			tentativeG += 10;
		}
		else
		{
			tentativeG += openEntry->getFGH('g');
			std::cout << "This should not be possible, even if it was!\n";
		}

		if (openEntry->getFGH('g') > tentativeG)
		{
			openEntry->setParent(parent);
			calculateFGH(openEntry, end);
			return true;
		}
	}

}

void AStarMain::AddNearby(AStarNode * node, AStarNode* end)
{
	Index parentIndex = node->GetIndex();
	AddNode(node, end, Index(parentIndex.first - 1, parentIndex.second));
	AddNode(node, end, Index(parentIndex.first + 1, parentIndex.second));
	AddNode(node, end, Index(parentIndex.first, parentIndex.second - 1));
	AddNode(node, end, Index(parentIndex.first - 1, parentIndex.second - 1));
	AddNode(node, end, Index(parentIndex.first + 1, parentIndex.second - 1));
	AddNode(node, end, Index(parentIndex.first, parentIndex.second + 1));
	AddNode(node, end, Index(parentIndex.first - 1, parentIndex.second + 1));
	AddNode(node, end, Index(parentIndex.first + 1, parentIndex.second + 1));
}



bool AStarMain::MoveToClosed(Index nodeIndex)
{
	auto it = openNodes.find(nodeIndex);
	if (it != openNodes.end() && closedNodes.find(nodeIndex) == closedNodes.end())
	{
		closedNodes.insert(std::pair<Index, AStarNode*>(it->first, it->second));
		openNodes.erase(it);

		return true;
	}
	else
	{
		return false;
	}
}

AStarNode * AStarMain::FindLowest()
{
	if (openNodes.size() <= 0)
	{
		return nullptr;
	}

	AStarNode* lowestNode = openNodes.begin()->second;
	int minF = lowestNode->getFGH('f');

	for (auto it : openNodes)
	{
		if (it.second->getFGH('h') == 0)
		{
			return it.second;
		}

		if (it.second->getFGH('f') <= minF)
		{
			lowestNode = it.second;
			minF = lowestNode->getFGH('f');
		}
	}

	return lowestNode;
}

std::vector<AStarNode*> AStarMain::FindAStarPath(std::vector<Index> blocked, Index startIndex, Index endIndex)
{
	reset();

	blockedTiles = blocked;

	if (startIndex.first >= Config::GRID_WIDTH || startIndex.first < 0 ||
		startIndex.second >= Config::GRID_HEIGHT || startIndex.second < 0)
	{
		path.clear();
		return path;
	}

	if (endIndex.first >= Config::GRID_WIDTH || endIndex.first < 0 ||
		endIndex.second >= Config::GRID_HEIGHT || endIndex.second < 0)
	{
		path.clear();
		return path;
	}

	AStarNode* start = new AStarNode(startIndex.first, startIndex.second, openNodeSprite, closedNodeSprite, nullptr);
	AStarNode* end = new AStarNode(endIndex.first, endIndex.second, openNodeSprite, closedNodeSprite, nullptr);
	openNodes.insert(std::pair<Index, AStarNode*>(startIndex, start));

	if (FindAStarPathRecursive(start, end))
	{
		for (auto it : path)
		{
			it->SetSprite(3);
		}
		return path;
	}
	else
	{
		path.clear();
		return path;
	}
}

bool AStarMain::FindAStarPathRecursive(AStarNode * start, AStarNode * end)
{
	if (!pathFound)
	{
		AddNearby(start, end);
		MoveToClosed(start->GetIndex());

		AStarNode* temp;
		temp = FindLowest();
		if (temp == nullptr || openNodes.size() == 0)
		{
			return pathFound;
		}

		if (temp->getFGH('h') == 0) //Reached end
		{
			pathFound = true;
			while (temp != nullptr)
			{
				path.push_back(temp);
				temp = temp->getParent();
			}
		}
		else
		{
			pathFound = FindAStarPathRecursive(temp, end);
		}
	}

	return pathFound;
}

