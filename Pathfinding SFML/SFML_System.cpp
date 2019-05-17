#include "stdafx.h"
#include "SFML_System.h"
#include "Config.h"
#include "IEntity.h"


SFML_System::SFML_System() : window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Pathfinding")
{
	spritesheet.loadFromFile("../Assets/spritesheetastar.png");
}


SFML_System::~SFML_System()
{
	if (window.isOpen())
	{
		window.close();
	}
}

void SFML_System::RenderClear()
{
	window.clear();
}

void SFML_System::DrawEntity(IEntity* entity)
{
	window.draw(entity->GetSprite());
}

void SFML_System::Display()
{
	window.display();
}

bool SFML_System::WindowStatus()
{
	return window.isOpen();
}

sf::Sprite SFML_System::CreateSprite(sf::IntRect srcRect)
{
	sf::Sprite sprite(spritesheet, srcRect);
	return sprite;
}

Index SFML_System::GetMousePosIndex()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return Index(mousePos.x / (Config::TILE_SIZE*Config::TILE_SCALE), mousePos.y / (Config::TILE_SIZE*Config::TILE_SCALE));
}

sf::Vector2i SFML_System::GetMousePosVector()
{
	return sf::Mouse::getPosition(window);
}

sf::RenderWindow * SFML_System::getWindow()
{
	return &window;
}
