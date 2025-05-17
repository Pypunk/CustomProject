#include "pch.h"
#include "Character.h"
#include "Sprite.h"

Character::Character(const Point2f& position)
	:GameObject{position}
	, m_CurrentState{ State::idle }
	, m_AttackTimer{0}
	, m_pIdleSprite(nullptr)
	, m_pRunSprite(nullptr)
	, m_pAttackSprite(nullptr)
	, m_pDyingSprite(nullptr)
{
	m_Shape.width = 50.f;
	m_Shape.height = 50.f;
}

Character::~Character()
{
}

void Character::Update(float elapsedSec)
{
	if (m_pRunSprite.get())
	{
		m_pRunSprite->Update(elapsedSec);
	}
	if (m_pIdleSprite.get())
	{
		m_pIdleSprite->Update(elapsedSec);
	}
	if (m_pAttackSprite.get())
	{
		m_pAttackSprite->Update(elapsedSec);
	}
	if (m_pDyingSprite.get())
	{
		m_pDyingSprite->Update(elapsedSec);
	}
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	if (m_CurrentState == State::attacking)
	{
		m_AttackTimer += elapsedSec;
		if (1.3f < m_AttackTimer)
		{
			m_AttackTimer = 0.f;
			m_CurrentState = State::idle;
		}
	}
}

void Character::Draw() const
{
	switch (m_CurrentState)
	{
	case Character::State::idle:
		if (m_pIdleSprite)
		{
			m_pIdleSprite->Draw(m_Shape);
		}
		break;
	case Character::State::running:
		if (m_pRunSprite)
		{
			m_pRunSprite->Draw(m_Shape);
		}
		break;
	case Character::State::attacking:
		if (m_pAttackSprite)
		{
			m_pAttackSprite->Draw(m_Shape);
		}
		break;
	case Character::State::dying:
		if (m_pDyingSprite)
		{
			m_pDyingSprite->Draw(m_Shape);
		}
		break;
	}
}

void Character::DoCollisions(const std::shared_ptr<GameObject> object, float elapsedSec)
{
	if (!object->GetPassable())
	{
		DoTopCollisions(object, elapsedSec);
		DoRightCollisions(object, elapsedSec);
		DoLeftCollisions(object, elapsedSec);
		DoBottomCollisions(object, elapsedSec);
	}
}

void Character::DoCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	DoTopCollisions(vertices, elapsedSec);
	DoRightCollisions(vertices, elapsedSec);
	DoLeftCollisions(vertices, elapsedSec);
	DoBottomCollisions(vertices, elapsedSec);
}

void Character::DoTopCollisions(const std::shared_ptr<GameObject> object, float elapsedSec)
{
	utils::HitInfo hitTop{};
	if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetTopCenter(), hitTop) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterRight(), GetCollisionShape().GetTopRight(), hitTop) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetTopLeft(), hitTop))
	{
		m_Shape.bottom -= m_Velocity.y * elapsedSec;
	}
}

void Character::DoTopCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
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
}

void Character::DoRightCollisions(const std::shared_ptr<GameObject> object, float elapsedSec)
{
	utils::HitInfo hitRight{};
	if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterRight(), hitRight) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopRight(), hitRight) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomRight(), hitRight))
	{
		m_Shape.left -= m_Velocity.x * elapsedSec;
	}
}

void Character::DoRightCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	utils::HitInfo hitRight{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterRight(), hitRight) ||
			utils::Raycast(i, GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopRight(), hitRight) ||
			utils::Raycast(i, GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomRight(), hitRight))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
	}
}

void Character::DoLeftCollisions(const std::shared_ptr<GameObject> object, float elapsedSec)
{
	utils::HitInfo hitLeft{};
	if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterLeft(-5.f, 0.f), hitLeft) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopLeft(), hitLeft) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomLeft(), hitLeft))
	{
		m_Shape.left -= m_Velocity.x * elapsedSec;
	}
}

void Character::DoLeftCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	utils::HitInfo hitLeft{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetCenterLeft(-5.f, 0.f), hitLeft) ||
			utils::Raycast(i, GetCollisionShape().GetTopCenter(), GetCollisionShape().GetTopLeft(), hitLeft) ||
			utils::Raycast(i, GetCollisionShape().GetBottomCenter(), GetCollisionShape().GetBottomLeft(), hitLeft))
		{
			m_Shape.left -= m_Velocity.x * elapsedSec;
		}
	}
}

void Character::DoBottomCollisions(const std::shared_ptr<GameObject> object, float elapsedSec)
{
	utils::HitInfo hitBottom{};
	if (utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenter(), GetCollisionShape().GetBottomCenter(0.f, -5.f), hitBottom) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterRight(), GetCollisionShape().GetBottomRight(), hitBottom) ||
		utils::Raycast(object->GetCollisionShape(), GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetBottomLeft(), hitBottom))
	{
		m_Shape.bottom -= m_Velocity.y * elapsedSec;
		m_Shape.bottom++;
	}
}

void Character::DoBottomCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	utils::HitInfo hitBottom{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, GetCollisionShape().GetCenter(), GetCollisionShape().GetBottomCenter(0.f, -5.f), hitBottom) ||
			utils::Raycast(i, GetCollisionShape().GetCenterRight(), GetCollisionShape().GetBottomRight(), hitBottom) ||
			utils::Raycast(i, GetCollisionShape().GetCenterLeft(), GetCollisionShape().GetBottomLeft(), hitBottom))
		{
			m_Shape.bottom -= m_Velocity.y * elapsedSec;
		}
	}
}

void Character::GetHit(const Rectf& damageShape)
{
	if (utils::IsOverlapping(m_Shape, damageShape))
	{
		m_CurrentHealth -= 10;
	}
}
