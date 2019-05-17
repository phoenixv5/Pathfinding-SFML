#pragma once
#include <SFML/Graphics.hpp>
#include "IEntity.h"

class SFML_System
{
	sf::Texture spritesheet;
	sf::RenderWindow window;
public:
	SFML_System();
	~SFML_System();
	void RenderClear();
	void DrawEntity(IEntity* entity);
	void Display();
	bool WindowStatus();
	sf::Sprite CreateSprite(sf::IntRect srcRect);
	Index GetMousePosIndex();
	sf::Vector2i GetMousePosVector();
	sf::RenderWindow * getWindow();
};

