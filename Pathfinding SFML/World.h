#pragma once
#include "Config.h"
#include "IEntity.h"

class SFML_System;
class Tile;
class AStarNode;
class AStarMain;
class Spaceship;
class TradingPost;
class StarChaser;
class FallenStar;
class StartButton;

class World
{
	SFML_System* core;
	std::vector<AStarNode*> path;
	AStarMain* wish;

	Tile* grid[Config::GRID_WIDTH][Config::GRID_HEIGHT];

	Spaceship* ship;
	FallenStar* star;
	TradingPost* trader;
	StarChaser* chaser;
	StartButton* button;

	bool objectSelected;
	bool pathfindingStarted;
	IEntity* selectedObject;

	void OnClick();
public:
	World();
	~World();
	void Update();
	Index GetObjectIndex(std::string objectType);
	std::vector<Index> calculateBlocked();
};

