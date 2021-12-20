#include "pch.h"
#include "Unit.h"

Unit::Unit(const Point2f& position, float size)
	:m_state{UnitState::deselected}
	, m_Shape{ position.x,position.y,size,size }
	,m_MoveLocation{GetMiddleOfRect(m_Shape)}
{
}

const void Unit::Draw()
{
	switch (m_state)
	{
	case Unit::UnitState::selected:
		FillRect(m_Shape);
		break;
	case Unit::UnitState::deselected:
		DrawRect(m_Shape);
		break;
	}
}

void Unit::MoveTo(float elapsedSec)
{
	Point2f middlePoint{ GetMiddleOfRect(m_Shape) };
	Vector2f direction{ m_MoveLocation.x - middlePoint.x,m_MoveLocation.y - middlePoint.y };
	m_Shape.left += direction.x * elapsedSec;
	m_Shape.bottom += direction.y * elapsedSec;
}

bool Unit::SelectUnit(const Point2f& mousePos)
{
	if (IsPointInRect(mousePos, m_Shape))
	{
		m_state = UnitState::selected;
		return true;
	}
	return false;
}

bool Unit::SelectUnit(const Rectf& selectionRect)
{
	if (IsOverlapping(m_Shape, selectionRect))
	{
		m_state = UnitState::selected;
		return true;
	}
	return false;
}

void Unit::SetMoveLocation(const Point2f& newLocation)
{
		if (m_state == UnitState::selected)
		{
			m_MoveLocation = newLocation;
		}
}

const Rectf Unit::GetShape()
{
	return m_Shape;
}

void Unit::Deselect()
{
	m_state = UnitState::deselected;
}
