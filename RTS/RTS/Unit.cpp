#include "pch.h"
#include "Unit.h"

Unit::Unit(const Point2f& position, float size)
	:m_state{UnitState::deselected}
	, m_Shape{ position.x,position.y,size,size }
	,m_MoveLocation{m_Shape.GetCenter()}
	,m_Color{1,1,1,1}
	, m_Text{ "Text","Fonts/Pineapple Days.otf",20,Color4f{} }
{
}

void Unit::Draw() const
{
	utils::SetColor(m_Color);
	switch (m_state)
	{
	case Unit::UnitState::selected:
		utils::FillRect(m_Shape);
		break;
	case Unit::UnitState::deselected:
		utils::DrawRect(m_Shape);
		break;
	}
	m_Text.Draw(m_Shape);
}

void Unit::MoveTo(float elapsedSec)
{
	Point2f middlePoint{ m_Shape.GetCenter() };
	Vector2f direction{ middlePoint,m_MoveLocation };
	m_Shape.left += direction.x * elapsedSec;
	m_Shape.bottom += direction.y * elapsedSec;
}

bool Unit::SelectUnit(const Point2f& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_Shape))
	{
		m_state = UnitState::selected;
		return true;
	}
	return false;
}

bool Unit::SelectUnit(const Rectf& selectionRect)
{
	if (utils::IsOverlapping(m_Shape, selectionRect))
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

void Unit::Select()
{
	m_state = UnitState::selected;
}

