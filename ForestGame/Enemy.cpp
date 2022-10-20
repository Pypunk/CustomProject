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
	Vector2f direction{ m_Shape.GetCenter(),player.GetCenter() };
	m_Velocity.x = direction.x;
	m_Velocity.y = direction.y;
	m_CurrentState = State::running;
	if (m_Shape.GetCenter().x > player.GetCenter().x)
	{
		m_pRunSprite->Flip(true);
	}
	if (m_Shape.GetCenter().x < player.GetCenter().x)
	{
		m_pRunSprite->Flip(false);
	}
	std::cout << direction;
}
