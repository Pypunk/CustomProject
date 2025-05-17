#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(const Point2f& position, float width, float height)
	:m_Shape{position,width,height}
	, m_Angle{}
	, m_IsSelected{false}
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
	if (utils::IsPointInRect(mousePos, m_Shape) || utils::IsOverlapping(m_Shape, selectionRect))
	{
		m_IsSelected = true;
	}
	else
	{
		m_IsSelected = false;
	}
}

void GameObject::AvoidOverlapWithOthers(const std::vector<GameObject*>& others, float elapsedSec)
{
	const float minDistance = m_Shape.width * 2.f;

	for (const GameObject* other : others)
	{
		if (other == this) continue;

		float distance = utils::GetDistance(GetCenter(), other->GetCenter());

		if (distance < minDistance && distance > 0.f)
		{
			Vector2f pushAway = Vector2f{ other->GetCenter(), GetCenter() }.Normalized();
			float pushStrength = (minDistance - distance) * 2.0f;

			m_Shape.left += pushAway.x * pushStrength * elapsedSec;
			m_Shape.bottom += pushAway.y * pushStrength * elapsedSec;
		}
	}
}
bool GameObject::IsPointBlocked(const Point2f& point, const std::vector<GameObject*>& others, float blockRadius) const
{
	for (const GameObject* other : others)
	{
		if (utils::GetDistance(other->GetCenter(), point) < blockRadius)
		{
			return true;
		}
	}
	return false;
}
