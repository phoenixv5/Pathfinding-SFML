#include "stdafx.h"
#include "Config.h"
#include "World.h"
#include "StarChaser.h"


void StarChaser::Pick()
{
	hasStar = true;
}

void StarChaser::Drop()
{
	hasStar = false;
}

void StarChaser::UpdateState()
{
	if ((worldRef->GetObjectIndex("TradingPost").first == GetIndex().first && worldRef->GetObjectIndex("TradingPost").second == GetIndex().second)&&hasStar)
	{
		currentState = FSM::Ended;
		dest = GetIndex();
		return;
	}
	
	if (worldRef->GetObjectIndex("FallenStar").first == GetIndex().first && worldRef->GetObjectIndex("FallenStar").second == GetIndex().second)
	{
		Pick();
	}

	if (worldRef->GetObjectIndex("SpaceShip").first == GetIndex().first && worldRef->GetObjectIndex("SpaceShip").second == GetIndex().second)
	{
		fatigued = false;
	}
	

	if (!hasStar&&!fatigued)
	{
		currentState = FSM::SeekStar;
		dest = worldRef->GetObjectIndex("FallenStar");
	}
	else if (hasStar&&fatigued)
	{
		Drop();
		currentState = FSM::SeekShip;
		dest = worldRef->GetObjectIndex("SpaceShip");
	}
	else if (hasStar && !fatigued)
	{
		currentState = FSM::SeekTrade;
		dest = worldRef->GetObjectIndex("TradingPost");
	}
}


Index StarChaser::GetDestination()
{
	return dest;
}

void StarChaser::SetDestination(Index changedDest)
{
	dest.first = changedDest.first;
	dest.second = changedDest.second;
}

void StarChaser::SetFatigueStatus(bool fatiguedStatus)
{
	fatigued = fatiguedStatus;
}

bool StarChaser::GetFatigueStatus()
{
	return fatigued;
}

bool StarChaser::GetStarStatus()
{
	return hasStar;
}

StarChaser::StarChaser(World* world, int x, int y, sf::Sprite sprite1, sf::Sprite sprite2) : IEntity(x, y, sprite1, sprite2)
{
	worldRef = world;
	dest = Index(x, y);
}


StarChaser::~StarChaser()
{
}
