#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"

Enemy::Enemy(const Point2f& position)
	:Character(position)
{
	m_MoveSpeed = 50.f;
}

void Enemy::MoveToPlayer(const Rectf& player)
{
	if (utils::GetDistance(player.GetCenter(),m_Shape.GetCenter()) > 10.f)
	{
		Vector2f direction{ m_Shape.GetCenter(),player.GetCenter() };
		direction = direction.Normalized() * m_MoveSpeed;
		m_Velocity.x = direction.x;
		m_Velocity.y = direction.y;
		m_CurrentState = State::running;
		m_pRunSprite->Flip(false);
	}
}
