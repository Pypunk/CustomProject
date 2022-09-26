#pragma once
class Sprite;
#include "Character.h"
class Player final :public Character
{
public:
	Player(const Point2f& position);

	void Update(float elapsedSec) override;
};

