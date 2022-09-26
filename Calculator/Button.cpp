#include "pch.h"
#include "Button.h"

Button::Button(const Point2f& position, float width, float height)
	:m_Shape{position,width,height}
{
}

void Button::Draw(const Point2f& mousePos) const
{
	Color4f color{};
	if (utils::IsPointInRect(mousePos, m_Shape))
	{
		color = Color4f{ 0.5f,0.5f,0.5f,0.5f };
	}
	else
	{
		color = Color4f{ 1.f,1.f,1.f,0.5f };
	}
	utils::SetColor(color);
	utils::FillRect(m_Shape);
	utils::SetColor(Color4f{});
	utils::DrawRect(m_Shape);
}

bool Button::ButtonClicked(const Point2f& mousePos) const
{
	return utils::IsPointInRect(mousePos, m_Shape);
}

Rectf Button::GetShape() const
{
	return m_Shape;
}
