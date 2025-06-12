#pragma once
#include "GameObject.h"
class PatrolPoints;
class Unit : public GameObject
{
public:
	enum class State
	{
		Face,
		Following,
		Patrolling
	};
	enum class UnitType
	{
		Villager,
		Infantry,
		Cavalry,
		Ranged
	};
	Unit(const Point2f& position);
	~Unit();

	void Draw() const override;
	void Update(std::vector<std::unique_ptr<GameObject>>& other,float elapsedSec) override;
	void Face(const Point2f& target, float elapsedSec);
	void Follow(const Point2f& target, float elapsedSec);
	void Patrol(float elapsedSec, std::vector<std::unique_ptr<GameObject>>& others);
	void ToggleState(State state);
	
	void CommandAI(const Point2f& target);
	void RemovePatrolPoints(const Point2f& target);
	void SetFormationOffset(const Point2f offset);
	void SetFacingTargetOffset(const Vector2f& offset);
	void DrawExtra() const override;

	int counter{};

	GameObjectType GetType() const override;
	virtual UnitType GetUnitType() const = 0;
private:
	State m_State;
	Point2f m_Target;
	float m_WalkSpeed;
	bool m_IsTaskGiven;
	PatrolPoints* m_pPatrolPoints;
	float m_TimeStuck{ 0.f };
	const float kMaxStuckTime{ 10.f };
	Point2f m_FormationOffset;
	Vector2f m_FacingTargetOffset;

	void SkipToNextPoint();
	bool m_UseCustomFacing;
};

