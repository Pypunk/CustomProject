#include "pch.h"
#include "SelectionRect.h"
#include <cmath>
SelectionRect::SelectionRect(const Rectf worldbounds)
	:m_isMousePressed{false}
	, m_StartPos{ -1,-1 }
	, m_WorldBounds{ worldbounds }
{
}

void SelectionRect::CreateRect(const Point2f& mousePos)
{
	if (m_isMousePressed)
	{
		float minX = std::min(m_StartPos.x, mousePos.x);
		float minY = std::min(m_StartPos.y, mousePos.y);
		float maxX = std::max(m_StartPos.x, mousePos.x);
		float maxY = std::max(m_StartPos.y, mousePos.y);

		const float gridSize = 1.f;
		minX = Snap(minX, gridSize);
		minY = Snap(minY, gridSize);
		maxY = Snap(maxY, gridSize);
		maxX = Snap(maxX, gridSize);

		minX = Clamp(minX, m_WorldBounds.left, m_WorldBounds.left + m_WorldBounds.width);
		minY = Clamp(minY, m_WorldBounds.bottom, m_WorldBounds.bottom + m_WorldBounds.height);
		maxY = Clamp(maxY, m_WorldBounds.bottom, m_WorldBounds.bottom + m_WorldBounds.height);
		maxX = Clamp(maxX, m_WorldBounds.left, m_WorldBounds.left + m_WorldBounds.width);

		m_Shape.SetBottomLeft(Point2f{ minX, minY });
		m_Shape.width = maxX - minX;
		m_Shape.height = maxY - minY;
	}
}

void SelectionRect::Draw() const
{
	if (m_isMousePressed)
	{
		utils::DrawRect(m_Shape);
	}
}

void SelectionRect::CreateStartPos(const Point2f& mousePos)
{
	m_StartPos = mousePos;
	m_isMousePressed = true;
}

void SelectionRect::RemoveRect()
{
	m_isMousePressed = false;
	m_Shape = Rectf{0,0,0,0};
}

Rectf SelectionRect::GetRect() const
{
	return m_Shape;
}

bool SelectionRect::IsActive() const
{
	return m_isMousePressed;
}

float SelectionRect::Snap(float value, float gridsize)
{
	return std::floor(value / gridsize) * gridsize;
}

float SelectionRect::Clamp(float value, float min, float max)
{
	return std::max(min, std::min(value, max));
}
