#include "pch.h"
#include "Unit.h"
#include <cmath>
#include "PatrolPoints.h"

Unit::Unit(const Point2f& position)
	:GameObject(position,50,50)
	, m_WalkSpeed{ 100.f }
	, m_IsTaskGiven{ false }
	, m_State{ State::Patrolling }
	, m_Target{}
	, m_pPatrolPoints{ new PatrolPoints{} }
	, m_FormationOffset{}
	, m_FacingTargetOffset{}
	, m_UseCustomFacing{ false }
{
}

Unit::~Unit()
{
	delete m_pPatrolPoints;
}

void Unit::Update(std::vector<GameObject*>& others, float elapsedSec)
{
	if (m_IsTaskGiven)
	{
		switch (m_State)
		{
		case State::Face:
			if (m_UseCustomFacing)
			{
				Face(m_Shape.GetCenter() + m_FacingTargetOffset, elapsedSec);
			}
			else 
			{
				Face(m_Target, elapsedSec);
			}
			break;
		case State::Following:
			Follow(m_Target, elapsedSec);
			if (utils::GetDistance(m_Shape.GetCenter(), m_Target) <= 10.f)
			{
				m_IsTaskGiven = false;
				m_UseCustomFacing = false;
			}
			AvoidOverlapWithOthers(others, elapsedSec);
			break;
		case State::Patrolling:
			Patrol(elapsedSec, others);
			AvoidOverlapWithOthers(others, elapsedSec);
			break;
		}
	}
}

void Unit::Face(const Point2f& target, float elapsedSec)
{
	Vector2f dir = Vector2f{ m_Shape.GetCenter(), target }.Normalized();
	m_Angle = utils::ConvertToDegrees(std::atan2(dir.y, dir.x));
}

void Unit::Follow(const Point2f& target, float elapsedSec)
{
	const float VectorScaler{ 100.f };
	if (m_UseCustomFacing) 
	{
		Face(target + m_FacingTargetOffset, elapsedSec);
	}
	else
	{
		Face(target, elapsedSec);
	}
	Vector2f direction{ m_Shape.GetCenter(),target };
	direction = direction.Normalized();
	direction *= VectorScaler;
	m_Shape.left += direction.x * elapsedSec;
	m_Shape.bottom += direction.y * elapsedSec;
}

void Unit::Patrol(float elapsedSec, std::vector<GameObject*>& others)
{
	m_Target = m_pPatrolPoints->GetPoints()[counter];
	Follow(m_Target, elapsedSec);

	float distance = utils::GetDistance(m_Shape.GetCenter(), m_Target);
	if (distance <= 10.f)
	{
		m_TimeStuck = 0.f; // reached successfully
		SkipToNextPoint();
	}
	else
	{
		m_TimeStuck += elapsedSec;
		if (m_TimeStuck >= kMaxStuckTime)
		{
			m_TimeStuck = 0.f;
			SkipToNextPoint();
		}
	}
	if (IsPointBlocked(m_Target, others))
	{
		SkipToNextPoint();
	}
}

void Unit::ToggleState(State state)
{
	if (IsSelected())
	{
		m_State = state;
	}
}

void Unit::CommandAI(const Point2f& target)
{
	if (IsSelected())
	{
		m_IsTaskGiven = true;
		if (m_State == State::Patrolling)
		{
			m_pPatrolPoints->AddPoint(target);
		}
		else
		{
			m_Target = Point2f{ target.x + m_FormationOffset.x,target.y + m_FormationOffset.y };
		}
	}
}

void Unit::RemovePatrolPoints(const Point2f& target)
{
	if (IsSelected())
	{
		m_pPatrolPoints->RemovePoint(target, counter);
	}
}

void Unit::SetFormationOffset(const Point2f offset)
{
	m_FormationOffset = offset;
}

void Unit::SetFacingTargetOffset(const Vector2f& offset)
{
	m_FacingTargetOffset = offset;
	m_UseCustomFacing = true;
}

void Unit::DrawExtra() const
{
	m_pPatrolPoints->DrawDebug();
}

GameObject::GameObjectType Unit::GetType() const
{
	return GameObject::GameObjectType::Unit;
}

void Unit::SkipToNextPoint()
{
	counter = (counter + 1) % m_pPatrolPoints->size();
}
