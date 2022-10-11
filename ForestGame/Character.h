#pragma once
#include "GameObject.h"
class Sprite;
class Character: public GameObject
{
public:
	Character(const Point2f& position);
	~Character();

	virtual void Update(float elapsedSec);
	virtual void Draw() const override;
	void DoCollisions(GameObject* object, float elapsedSec);
	void DoCollisions(std::vector < std::vector<Point2f>>& vertices, float elapsedSec);
protected:
	enum class State
	{
		idle,
		running,
		attacking,
		dying
	};
	State m_CurrentState;
	Sprite* m_pIdleSprite;
	Sprite* m_pRunSprite;
	Sprite* m_pAttackSprite;
	Sprite* m_pDyingSprite;
	Vector2f m_Velocity;
	float m_MoveSpeed;
};

