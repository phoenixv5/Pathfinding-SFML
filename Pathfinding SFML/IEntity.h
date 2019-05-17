#pragma once
#include <map>
#include <SFML/Graphics.hpp>

typedef std::pair<int, int> Index;

class IEntity
{
private:
	Index index;
protected:
	int currentSprite;
	sf::Sprite sprite[2];
public:
	IEntity(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~IEntity();

	Index GetIndex();
	virtual sf::Sprite GetSprite();
	virtual void SetSprite(int n);
	virtual void SetPos(int x, int y);

};

