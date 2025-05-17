#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"

static const float animationSpeed{ 1 / 5.f };
static const float moveSpeed{ 90.f };
static const float detectionRange{ 200.f };

Enemy::Enemy(const Point2f& position)
	:Character(position)
{
}

void Enemy::MoveToPlayer(const Rectf& player)
{

	const float distanceToPlayer{ utils::GetDistance(m_Shape.GetCenter(),player.GetCenter()) };

	if (distanceToPlayer <= detectionRange && !utils::IsOverlapping(m_Shape,player))
	{
		if (m_AttackTimer <= 0) {
			if (m_Shape.GetCenter().x < player.GetCenter().x)
			{
				m_Velocity.x = moveSpeed;
				m_pRunSprite->Flip(false);
				m_pAttackSprite->Flip(false);
			}
			if (m_Shape.GetCenter().x > player.GetCenter().x)
			{
				m_Velocity.x = -moveSpeed;
				m_pRunSprite->Flip(true);
				m_pAttackSprite->Flip(true);
			}
			if (m_Shape.GetCenter().y < player.GetCenter().y)
			{
				m_Velocity.y = moveSpeed;
			}
			if (m_Shape.GetCenter().y > player.GetCenter().y)
			{
				m_Velocity.y = -moveSpeed;
			}
			m_pAttackSprite->Reset();
			m_CurrentState = State::running;
		}
	}
	else if (utils::IsOverlapping(m_Shape, player))
	{
		m_Velocity = Vector2f{ 0,0 };
		if (m_AttackTimer <= 0)
		{
			m_CurrentState = State::attacking;
		}
	}
	else
	{
		m_Velocity = Vector2f{ 0,0 };
		m_CurrentState = State::idle;
		m_pAttackSprite->Reset();
	}
}
