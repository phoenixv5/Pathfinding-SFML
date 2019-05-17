#pragma once
#include <SFML/Graphics.hpp>

class Config
{
public:
	const static sf::IntRect TILE_TEXTURE_RECT[2];
	const static sf::IntRect NODE_TEXTURE_RECT[2];

	const static sf::IntRect STARTBUTTON_TEXTURE_RECT[2];

	const static sf::IntRect SHIP_TEXTURE_RECT[2];
	const static sf::IntRect STAR_TEXTURE_RECT[2];
	const static sf::IntRect TRADEPOST_TEXTURE_RECT[2];
	const static sf::IntRect STARCHASER_TEXTURE_RECT[2];

	const static float TILE_SCALE;

	const static int GRID_WIDTH = 20;
	const static int GRID_HEIGHT = 20;
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;
	const static int TILE_SIZE = 128;

	const static int STARCHASER_ENERGY = 50;

	const static int BLOCKED_COUNT_START = 100;
};
