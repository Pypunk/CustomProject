#include "pch.h"
#include "SelectionRect.h"

SelectionRect::SelectionRect()
	:m_Pressed{false}
{
}

const void SelectionRect::Draw()
{
	if (m_Pressed)
	{
		DrawRect(m_Shape);
	}
}

void SelectionRect::UpdateRect(const Point2f& mousePos)
{
	m_Shape = Rectf{ m_FirstPos.x,m_FirstPos.y,-(m_FirstPos.x - mousePos.x),-(m_FirstPos.y - mousePos.y) };
	if (m_Shape.height < 0 && m_Shape.width < 0)
	{
		m_Shape = Rectf{ mousePos.x,mousePos.y,-(mousePos.x - m_FirstPos.x),-(mousePos.y - m_FirstPos.y) };
	}
	if (m_Shape.height < 0 && m_Shape.width > 0)
	{
		m_Shape = Rectf{ m_FirstPos.x,mousePos.y,-(m_FirstPos.x - mousePos.x),-(mousePos.y - m_FirstPos.y) };
	}
	if (m_Shape.height > 0 && m_Shape.width < 0)
	{
		m_Shape = Rectf{ mousePos.x,m_FirstPos.y,-(mousePos.x - m_FirstPos.x),-(m_FirstPos.y - mousePos.y) };
	}
}

void SelectionRect::SetFirstPos(const Point2f& position)
{
	m_Pressed = true;
	m_FirstPos = position;
}

void SelectionRect::SetReleased()
{
	m_Pressed = false;
	m_Shape = Rectf{};
}

const Rectf SelectionRect::GetShape()
{
	return m_Shape;
}
