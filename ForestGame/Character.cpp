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
	utils::DrawRect(m_Shape);
}

void Character::DoCollisions(GameObject* object)
{
	const Rectf collisionShape{ m_Shape.GetBottomLeft(),m_Shape.width,m_Shape.height / 2.f };
	if (!object->GetPassable())
	{
		utils::HitInfo hitTop{};
		if (utils::Raycast(object->GetCollisionShape(), collisionShape.GetCenter(), collisionShape.GetTopCenter(), hitTop))
		{
			m_Shape.bottom = hitTop.intersectPoint.y - collisionShape.height;
		}
		utils::HitInfo hitRight{};
		if (utils::Raycast(object->GetCollisionShape(), collisionShape.GetCenter(), collisionShape.GetCenterRight(), hitRight))
		{
			m_Shape.left = hitRight.intersectPoint.x - m_Shape.width;
		}
		utils::HitInfo hitBottom{};
		if (utils::Raycast(object->GetCollisionShape(), collisionShape.GetCenter(), collisionShape.GetBottomCenter(0.f, -5.f), hitBottom))
		{
			m_Shape.bottom = hitBottom.intersectPoint.y + 5.f;
		}
		utils::HitInfo hitLeft{};
		if (utils::Raycast(object->GetCollisionShape(), collisionShape.GetCenter(), collisionShape.GetCenterLeft(-5.f, 0.f), hitLeft))
		{
			m_Shape.left = hitLeft.intersectPoint.x + 5.f;
		}
	}
}

void Character::DoCollisions(std::vector<std::vector<Point2f>>& vertices)
{
	const Rectf collisionShape{ m_Shape.GetBottomLeft(),m_Shape.width,m_Shape.height / 2.f };
	utils::HitInfo hitTop{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, collisionShape.GetCenter(), collisionShape.GetTopCenter(), hitTop))
		{
			m_Shape.bottom = hitTop.intersectPoint.y - collisionShape.height;
		}
	}
	utils::HitInfo hitRight{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, collisionShape.GetCenter(), collisionShape.GetCenterRight(), hitRight))
		{
			m_Shape.left = hitRight.intersectPoint.x - m_Shape.width;
		}
	}
	utils::HitInfo hitBottom{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, collisionShape.GetCenter(), collisionShape.GetBottomCenter(0.f, -5.f), hitBottom))
		{
			m_Shape.bottom = hitBottom.intersectPoint.y + 5.f;
		}
	}
	utils::HitInfo hitLeft{};
	for (const std::vector<Point2f>& i : vertices)
	{
		if (utils::Raycast(i, collisionShape.GetCenter(), collisionShape.GetCenterLeft(-5.f, 0.f), hitLeft))
		{
			m_Shape.left = hitLeft.intersectPoint.x + 5.f;
		}
	}
}