#pragma once
#include "IEntity.h"

class World;

enum FSM
{
	SeekStar,
	SeekShip,
	SeekTrade,
	Ended
};

class StarChaser : public IEntity
{
	bool fatigued;
	bool hasStar;
	Index dest;
	World* worldRef;
public:
	FSM currentState;
	void Pick();
	void Drop();
	void UpdateState();
	Index GetDestination();
	void SetDestination(Index changedDest);

	void SetFatigueStatus(bool fatiguedStatus);
	bool GetFatigueStatus();
	bool GetStarStatus();

	StarChaser(World* world, int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~StarChaser();
};

