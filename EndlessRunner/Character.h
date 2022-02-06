#pragma once
#include "Vector2f.h"
class Sprite;
class Tile;
class Character
{
public:
	Character(const Point2f& position);
	~Character();

	const void Draw();
	void Update(float elapsedSec);
	void Jump();
	void DoPlatformCollision(Tile* tile);
private:
	enum class State
	{
		jumping,
		onGround
	};
	State m_CurrentState{State::onGround};
	Rectf m_Shape;
	Vector2f m_Velocity;
	float m_Gravity;
	Sprite* m_pTexture;
};

