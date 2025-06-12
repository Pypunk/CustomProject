#include "pch.h"
#include "Unit.h"
#include <cmath>
#include "PatrolPoints.h"

Unit::Unit(const Point2f& position)
	:GameObject(position,50,50)
	, m_WalkSpeed{ 100.f }
	, m_IsTaskGiven{ false }
	, m_State{ State::Following }
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

void Unit::Draw() const
{
	switch (GetUnitType())
	{
	case UnitType::Villager:
		utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });
		break;
	case UnitType::Infantry:
		utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		break;
	}
	GameObject::Draw();
}

void Unit::Update(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec)
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
			AvoidOverlapWithOthers(other, elapsedSec);
			break;
		case State::Patrolling:
			Patrol(elapsedSec, other);
			AvoidOverlapWithOthers(other, elapsedSec);
			break;
		}
	}
	m_MaxHealth.left = m_Shape.left;
	m_MaxHealth.bottom = m_Shape.GetTopCenter().y + 5.f;
	m_CurrentHealth.left = m_MaxHealth.left;
	m_CurrentHealth.bottom = m_MaxHealth.bottom;
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

void Unit::Patrol(float elapsedSec, std::vector<std::unique_ptr<GameObject>>& others)
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
	m_IsTaskGiven = true;
	m_Target = target;
	m_State = State::Following;
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
