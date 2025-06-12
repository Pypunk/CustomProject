#include "pch.h"
#include "GameObject.h"
#include <iostream>


GameObject::GameObject(const Point2f& position, float width, float height)
	:m_Shape{position,width,height}
	, m_Angle{}
	, m_IsSelected{false}
	, m_MaxHealth{ position.x,m_Shape.GetTopCenter().y + 5.f,width,10.f }
	, m_CurrentHealth{ position.x,m_MaxHealth.bottom,width,m_MaxHealth.height }
{
	m_ForwardVector = m_Shape.GetCenterRight() - m_Shape.GetCenterRight(-m_Shape.width);
}

void GameObject::Draw() const
{
	glPushMatrix();
	glTranslatef(GetCenter().x, GetCenter().y, 0.f);
	glRotatef(m_Angle, 0.f, 0.f, 1.f);
	glTranslatef(-GetCenter().x, -GetCenter().y, 0.f);
	utils::DrawRect(m_Shape);
	if (m_IsSelected)
	{
		utils::FillRect(m_Shape);
	}
	if (GetType() == GameObjectType::Unit || GetType() == GameObjectType::Projectile)
	{
		utils::DrawVector(m_Shape.GetCenter(), m_ForwardVector);
	}
	glPopMatrix();
	if (IsSelected())
	{
		utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		utils::FillRect(m_CurrentHealth);
		utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		utils::DrawRect(m_MaxHealth);
	}
	DrawExtra();
}

const Rectf& GameObject::GetShape() const
{
	return m_Shape;
}

Point2f GameObject::GetCenter() const
{
	return m_Shape.GetCenter();
}

bool GameObject::IsSelected() const
{
	return m_IsSelected;
}

void GameObject::SetSelected(const Point2f& mousePos, const Rectf& selectionRect)
{
	try
	{
		const Rectf& shape = GetShape(); // <- if this throws or is dangling, crash

		m_IsSelected = utils::IsPointInRect(mousePos, shape) ||
			utils::IsOverlapping(shape, selectionRect);
	}
	catch (...)
	{
		std::cout << "[ERROR] Exception in SetSelected — possibly due to invalid shape\n";
		m_IsSelected = false;
	}
}

void GameObject::AvoidOverlapWithOthers(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec)
{
	const float minDistance = m_Shape.width * 2.f;

	for (const std::unique_ptr<GameObject>& others : other)
	{
		if (others.get() == this) continue;

		float distance = utils::GetDistance(GetCenter(), others->GetCenter());

		if (distance < minDistance && distance > 0.f)
		{
			Vector2f pushAway = Vector2f{ others->GetCenter(), GetCenter() }.Normalized();
			float pushStrength = (minDistance - distance) * 2.0f;

			m_Shape.left += pushAway.x * pushStrength * elapsedSec;
			m_Shape.bottom += pushAway.y * pushStrength * elapsedSec;
		}
	}
}
bool GameObject::IsPointBlocked(const Point2f& point, std::vector<std::unique_ptr<GameObject>>& other, float blockRadius) const
{
	for (const std::unique_ptr<GameObject>& others : other)
	{
		if (utils::GetDistance(others->GetCenter(), point) < blockRadius)
		{
			return true;
		}
	}
	return false;
}
