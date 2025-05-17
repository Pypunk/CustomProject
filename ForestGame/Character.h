#pragma once
#include "GameObject.h"
#include <memory>
class Sprite;
class Character: public GameObject
{
public:
	Character(const Point2f& position);
	~Character();

	virtual void Update(float elapsedSec);
	virtual void Draw() const override;
	void DoCollisions(const std::shared_ptr<GameObject> object, float elapsedSec);
	void DoCollisions(const std::vector < std::vector<Point2f>>& vertices, float elapsedSec);
	void DoTopCollisions(const std::shared_ptr<GameObject> object, float elapsedSec);
	void DoTopCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void DoRightCollisions(const std::shared_ptr<GameObject> object, float elapsedSec);
	void DoRightCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void DoLeftCollisions(const std::shared_ptr<GameObject> object, float elapsedSec);
	void DoLeftCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void DoBottomCollisions(const std::shared_ptr<GameObject> object, float elapsedSec);
	void DoBottomCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void GetHit(const Rectf& damageShape);
protected:
	enum class State
	{
		idle,
		running,
		attacking,
		dying
	};
	State m_CurrentState;
	std::unique_ptr<Sprite> m_pIdleSprite;
	std::unique_ptr<Sprite> m_pRunSprite;
	std::unique_ptr<Sprite> m_pAttackSprite;
	std::unique_ptr<Sprite> m_pDyingSprite;
	Vector2f m_Velocity;
	float m_AttackTimer;
	float m_CurrentHealth;
	float m_MaxHealth;
};

