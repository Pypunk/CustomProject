#pragma once
class Platform;
class Sprite;
using namespace utils;
class Character
{
public:
	Character(const Point2f& position, float size);
	~Character();
	void Draw();
	void Update(float elapsedSec);
	void UpdateCollision(Platform& platform);
	const Rectf GetShape();
	void Jump();
private:
	Rectf m_Shape;
	Vector2f m_Velocity;
	Sprite* m_pSprite;
	float m_Gravity;
	bool m_Jumping;
	enum class CharacterState
	{
		jumping,
		running,
		standing
	};
	CharacterState m_State;
};

