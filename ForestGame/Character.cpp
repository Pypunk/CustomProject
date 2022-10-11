#include "pch.h"
#include "Character.h"
#include "Sprite.h"

Character::Character(const Point2f& position)
	:GameObject{position}
	, m_CurrentState{ State::idle }
	, m_MoveSpeed{ 100.f }
	, m_pIdleSprite{ nullptr }
	, m_pRunSprite{ nullptr }
	, m_pAttackSprite{ nullptr }
	, m_pDyingSprite{ nullptr }
{
	m_Shape.width = 50.f;
	m_Shape.height = 50.f;
}

Character::~Character()
{
	if (m_pIdleSprite)
	{
		delete m_pIdleSprite;
	}
	if (m_pRunSprite)
	{
		delete m_pRunSprite;
	}
	if (m_pAttackSprite)
	{
		delete m_pAttackSprite;
	}
	if (m_pDyingSprite)
	{
		delete m_pDyingSprite;
	}
}

void Character::Update(float elapsedSec)
{
	if (m_pRunSprite)
	{
		m_pRunSprite->Update(elapsedSec);
	}
	if (m_pIdleSprite)
	{
		m_pIdleSprite->Update(elapsedSec);
	}
	if (m_pAttackSprite)
	{
		m_pAttackSprite->Update(elapsedSec);
	}
	if (m_pDyingSprite)
	{
		m_pDyingSprite->Update(elapsedSec);
	}
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void Character::Draw() const
{
	switch (m_CurrentState)
	{
	case Character::State::idle:
		m_pIdleSprite->Draw(m_Shape);
		break;
	case Character::State::running:
		m_pRunSprite->Draw(m_Shape);
		break;
	case Character::State::attacking:
		m_pAttackSprite->Draw(m_Shape);
		break;
	case Character::State::dying:
		m_pDyingSprite->Draw(m_Shape);
		break;
	}
}

void Character::DoCollisions(GameObject* object, float elapsedSec)
{
	if (!object->GetPassable())
	{
		utils::HitInfo hitTop{};
		if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetTopCenter(), hitTop) ||
			utils::Raycast(object->GetCollisionShape(),GetCollisionShape().GetCenterRight(),GetCollisionShape().GetTopRight(),hitTop) ||
			utils::Raycast(object->GetCollisionShape(),GetCollisionShape().GetCenterLeft(),GetCollisionShape().GetTopLeft(),hitTop))
		{
			m_Shape.bottom -= m_Velocity.y * elapsedSec;
		}
		utils::HitInfo hitRight{};
		if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterRight(), hitRight) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopRight(), hitTop) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomRight(), hitTop))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
		utils::HitInfo hitBottom{};
		if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetBottomCenter(0.f, -5.f), hitBottom) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterRight(), GetCollisionShape().GetBottomRight(), hitTop) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetBottomLeft(), hitTop))
		{
			m_Shape.bottom -= m_Velocity.y * elapsedSec;
			m_Shape.bottom++;
		}
		utils::HitInfo hitLeft{};
		if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterLeft(-5.f, 0.f), hitLeft) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopLeft(), hitTop) ||
			utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomLeft(), hitTop))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
	}
}

void Character::DoCollisions(std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	utils::HitInfo hitTop{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetTopCenter(), hitTop) ||
			utils::Raycast(i, GetCollisionShape().GetCenterRight(), GetCollisionShape().GetTopRight(), hitTop) ||
			utils::Raycast(i, GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetTopLeft(), hitTop))
		{
			m_Shape.bottom -= m_Velocity.y * elapsedSec;
		}
	}
	utils::HitInfo hitRight{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterRight(), hitRight) ||
			utils::Raycast(i, GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopRight(), hitTop) ||
			utils::Raycast(i, GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomRight(), hitTop))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
	}
	utils::HitInfo hitBottom{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetBottomCenter(0.f, -5.f), hitBottom) ||
			utils::Raycast(i, GetCollisionShape().GetCenterRight(), GetCollisionShape().GetBottomRight(), hitTop) ||
			utils::Raycast(i, GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetBottomLeft(), hitTop))
		{
			m_Shape.bottom -= m_Velocity.y * elapsedSec;
		}
	}
	utils::HitInfo hitLeft{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterLeft(-5.f, 0.f), hitLeft) ||
			utils::Raycast(i, GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopLeft(), hitTop) ||
			utils::Raycast(i, GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomLeft(), hitTop))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
	}
}