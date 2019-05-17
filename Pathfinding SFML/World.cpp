#include "stdafx.h"
#include "SFML_System.h"
#include "AStarMain.h"
#include "Tile.h"
#include "FallenStar.h"
#include "StarChaser.h"
#include "Spaceship.h"
#include "TradingPost.h"
#include "StartButton.h"
#include "World.h"
#include <iostream>


World::World()
{
	core = new SFML_System();
	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			grid[i][j] = new Tile(i, j, core->CreateSprite(Config::TILE_TEXTURE_RECT[0]), core->CreateSprite(Config::TILE_TEXTURE_RECT[1]));
		}
	}


	std::srand(std::time(nullptr));
	int x, y;

	for (int i = 0;i < Config::BLOCKED_COUNT_START;)
	{
		x = std::rand() % Config::GRID_WIDTH;
		y = std::rand() % Config::GRID_HEIGHT;
		if (!grid[x][y]->getBlockedStatus())
		{
			grid[x][y]->setBlockedStatus(true);
			i++;
		}
	}

	while (grid[x][y]->getBlockedStatus())
	{
		x = std::rand() % Config::GRID_WIDTH;
		y = std::rand() % Config::GRID_HEIGHT;
	}
	chaser = new StarChaser(this, x, y, core->CreateSprite(Config::STARCHASER_TEXTURE_RECT[0]), core->CreateSprite(Config::STARCHASER_TEXTURE_RECT[1]));

	while (grid[x][y]->getBlockedStatus() || (x == chaser->GetIndex().first && y == chaser->GetIndex().second))
	{
		x = std::rand() % Config::GRID_WIDTH;
		y = std::rand() % Config::GRID_HEIGHT;
	}
	star = new FallenStar(x, y, core->CreateSprite(Config::STAR_TEXTURE_RECT[0]), core->CreateSprite(Config::STAR_TEXTURE_RECT[1]));

	while (grid[x][y]->getBlockedStatus() || (x == chaser->GetIndex().first && y == chaser->GetIndex().second)
		|| (x == star->GetIndex().first && y == star->GetIndex().second))
	{
		x = std::rand() % Config::GRID_WIDTH;
		y = std::rand() % Config::GRID_HEIGHT;
	}
	ship = new Spaceship(x, y, core->CreateSprite(Config::SHIP_TEXTURE_RECT[0]), core->CreateSprite(Config::SHIP_TEXTURE_RECT[1]));

	while (grid[x][y]->getBlockedStatus() || (x == chaser->GetIndex().first && y == chaser->GetIndex().second)
		|| (x == star->GetIndex().first && y == star->GetIndex().second)
		|| (x == ship->GetIndex().first && y == ship->GetIndex().second)
		)
	{
		x = std::rand() % Config::GRID_WIDTH;
		y = std::rand() % Config::GRID_HEIGHT;
	}
	trader = new TradingPost(x, y, core->CreateSprite(Config::TRADEPOST_TEXTURE_RECT[0]), core->CreateSprite(Config::TRADEPOST_TEXTURE_RECT[1]));

	wish = new AStarMain(
		core->CreateSprite(Config::NODE_TEXTURE_RECT[0]),
		core->CreateSprite(Config::NODE_TEXTURE_RECT[1]));

	button = new StartButton(0, Config::GRID_HEIGHT, core->CreateSprite(Config::STARTBUTTON_TEXTURE_RECT[0]), core->CreateSprite(Config::STARTBUTTON_TEXTURE_RECT[1]));

	pathfindingStarted = false;
}


World::~World()
{
}

void World::Update()
{
	while (core->WindowStatus())
	{

		sf::Event event;
		while (core->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				core->getWindow()->close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				OnClick();
			}
		}

		core->RenderClear();

		for (int i = 0;i < Config::GRID_WIDTH;i++)
		{
			for (int j = 0;j < Config::GRID_HEIGHT;j++)
			{
				core->DrawEntity(grid[i][j]);
			}
		}

		for (auto it : path)
		{
			core->DrawEntity(it);
		}

		core->DrawEntity(ship);
		core->DrawEntity(trader);
		core->DrawEntity(star);
		core->DrawEntity(chaser);
		core->DrawEntity(button);

		core->Display();
	}
}

Index World::GetObjectIndex(std::string objectType)
{
	if (objectType == "StarChaser")
	{
		return chaser->GetIndex();
	}
	else if (objectType == "SpaceShip")
	{
		return ship->GetIndex();
	}
	else if (objectType == "TradingPost")
	{
		return trader->GetIndex();
	}
	else if (objectType == "FallenStar")
	{
		return star->GetIndex();
	}

	return Index(0, 0);
}

void World::OnClick()
{
	Index mouseIndex;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseIndex = core->GetMousePosIndex();
	}
	else
	{
		return;
	}


	if (pathfindingStarted)
	{
		path.clear();

		chaser->UpdateState();

		if (chaser->currentState == FSM::SeekShip)
		{
			path = wish->FindAStarPath(calculateBlocked(), chaser->GetIndex(), ship->GetIndex());
		}
		else if (chaser->currentState == FSM::SeekStar)
		{
			path = wish->FindAStarPath(calculateBlocked(), chaser->GetIndex(), star->GetIndex());
		}
		else if (chaser->currentState == FSM::SeekTrade)
		{
			path = wish->FindAStarPath(calculateBlocked(), chaser->GetIndex(), trader->GetIndex());
		}
		else if (chaser->currentState == FSM::Ended)
		{
			path.clear();
		}
		std::reverse(path.begin(), path.end());

		if (chaser->GetStarStatus())
		{
			for (int i = 0; i < path.size(); i++)
			{
				if (path[i]->getFGH('g') > Config::STARCHASER_ENERGY)
				{
					path[i]->SetSprite(1);
				}
				else
				{
					chaser->SetDestination(path[i]->GetIndex());
				}
			}

			star->SetPos(chaser->GetDestination().first, chaser->GetDestination().second);
			chaser->SetFatigueStatus(true);
		}

		chaser->SetPos(chaser->GetDestination().first, chaser->GetDestination().second);
	}
	else
	{
		if (
			core->GetMousePosVector().x >= button->GetSprite().getPosition().x
			&& core->GetMousePosVector().y >= button->GetSprite().getPosition().y
			&& core->GetMousePosVector().x <= button->GetSprite().getPosition().x + button->GetSprite().getGlobalBounds().width
			&& core->GetMousePosVector().y <= button->GetSprite().getPosition().y + button->GetSprite().getGlobalBounds().height
			)
		{
			pathfindingStarted = true;
			button->SetSprite(1);
		}


		if (mouseIndex.first < 0 || mouseIndex.second < 0 || mouseIndex.first >= Config::GRID_WIDTH || mouseIndex.second >= Config::GRID_HEIGHT)
		{
			return;
		}

		if (!objectSelected)
		{
			if (mouseIndex.first == chaser->GetIndex().first && mouseIndex.second == chaser->GetIndex().second)
			{
				objectSelected = true;
				selectedObject = chaser;
				selectedObject->SetSprite(1);
			}
			else if (mouseIndex.first == trader->GetIndex().first && mouseIndex.second == trader->GetIndex().second)
			{
				objectSelected = true;
				selectedObject = trader;
				selectedObject->SetSprite(1);
			}
			else if (mouseIndex.first == ship->GetIndex().first && mouseIndex.second == ship->GetIndex().second)
			{
				objectSelected = true;
				selectedObject = ship;
				selectedObject->SetSprite(1);
			}
			else if (mouseIndex.first == star->GetIndex().first && mouseIndex.second == star->GetIndex().second)
			{
				objectSelected = true;
				selectedObject = star;
				selectedObject->SetSprite(1);
			}
			else
			{
				grid[mouseIndex.first][mouseIndex.second]->setBlockedStatus(!grid[mouseIndex.first][mouseIndex.second]->getBlockedStatus());
			}
		}
		else
		{
			if (selectedObject != nullptr)
			{
				grid[mouseIndex.first][mouseIndex.second]->setBlockedStatus(false);
				selectedObject->SetPos(mouseIndex.first, mouseIndex.second);
				selectedObject->SetSprite(0);
			}
			objectSelected = false;
			selectedObject = nullptr;
		}
	}


}

std::vector<Index> World::calculateBlocked()
{
	std::vector<Index> blockedTiles;

	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			if (grid[i][j]->getBlockedStatus())
			{
				blockedTiles.push_back(grid[i][j]->GetIndex());
			}
		}
	}

	return blockedTiles;
}
