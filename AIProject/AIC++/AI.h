#pragma once
class PatrolPoints;
class AI
{
public:
	enum class State
	{
		Face,
		Following,
		Evading,
		Patrolling
	};
	AI(const Point2f& position);

	void Draw() const;
	void Face(const Point2f& target, float elapsedSec);
	void Follow(const Point2f& target, float elapsedSec);
	void Evade(const Point2f& target, float elapsedSec);
	void Patrol(PatrolPoints& points, float elapsedSec);
private:
	Rectf m_Shape;
	Vector2f m_ForwardVector;
	float m_Angle;
	int counter{};
	float m_WalkSpeed;
};

