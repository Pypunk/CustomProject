#include "pch.h"
#include "Platform.h"

Platform::Platform(const Point2f& position, float width, float height)
	:m_Shape{position.x,position.y,width,height}
{
}

Platform::Platform(const Rectf& rect)
	:m_Shape{rect}
{
}

void Platform::Draw()
{
	DrawRect(m_Shape);
}

bool Platform::IsOnPlatform(const Rectf& actor)
{
	return (IsOverlapping(actor, m_Shape));
}

void Platform::UpdatePlatform(float xCamPos)
{
	if (m_Shape.left <= xCamPos)
	{
		xCamPos += m_Shape.width;
	}
}

float Platform::GetTop()
{
	return m_Shape.bottom + m_Shape.height;
}

const Rectf Platform::GetShape()
{
	return m_Shape;
}
