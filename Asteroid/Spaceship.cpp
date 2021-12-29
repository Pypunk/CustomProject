#include "pch.h"
#include "Spaceship.h"
#include "utils.h"
#include <iostream>
#include "Health.h"

Spaceship::Spaceship(const Point2f& position, float size)
	:m_Shape{position.x-size/2.f,position.y-size/2.f,size,size}
	, m_Texture{}
	,m_CenterPoint{position}
	,m_IsShooting{true}
	,m_Rocket{position,size/5.f}
	,m_TargetPoint{position}
	,m_IsInvincible{true}
	,m_Time{}
	,m_pHealth{new Health{2}}
{
	//TextureFromFile("", m_Texture);
	std::cout << m_pHealth->ToString();
	TextureFromString(m_pHealth->ToString(), "Resources/DIN-Light.otf", 50, Color4f{ 1,1,1,1 }, m_HealthText);
	std::string invincibleString{ "Invincibility: " };
	invincibleString += std::to_string(m_Time);
	TextureFromString(invincibleString, "Resources/DIN-Light.otf", 20, Color4f{ 1,1,1,1 }, m_InvincibleText);
}

Spaceship::~Spaceship()
{
	DeleteTexture(m_Texture);
	DeleteTexture(m_HealthText);
	DeleteTexture(m_InvincibleText);
	delete m_pHealth;
	m_pHealth = nullptr;
}

void Spaceship::Draw(float windowWidth, float windowHeight)
{
	Color4f color{ 1,1,1,1 };
	if (m_IsInvincible)
	{
		color.a = 0.5f;
	}
	else
	{
		color.a = 1.f;
	}
	SetColor(color);
	FillRect(m_Shape);
	FillCircle(m_Rocket);
	Point2f healthTextPos{};
	DrawTexture(m_HealthText,healthTextPos);
	if (m_IsInvincible)
	{
		Point2f invincibleTextPos{ windowWidth - m_InvincibleText.width,windowHeight - m_InvincibleText.height };
		DrawTexture(m_InvincibleText, invincibleTextPos);
	}
}

void Spaceship::Update(float elapsedSec, float windowWidth, float windowHeight)
{
	const float invincibleSeconds{ 5.f };
	if (m_IsInvincible)
	{
		m_Time += elapsedSec;
		DeleteTexture(m_InvincibleText);
		std::string invincibleString{ "Invincibility: " };
		invincibleString += std::to_string(int(6-m_Time));
		TextureFromString(invincibleString, "Resources/DIN-Light.otf", 20, Color4f{ 1,1,1,1 }, m_InvincibleText);
		if (invincibleSeconds < m_Time)
		{
			std::cout << int(m_Time) << " seconds have passed, no longer invincible\n";
			m_Time = 0;
			m_IsInvincible = false;
		}
	}
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	UpdateBottom(windowHeight);
	UpdateLeft(windowWidth);
	if (m_IsShooting)
	{
		UpdateRocket(elapsedSec);
	}
	else
	{
		m_Rocket.center = GetMiddle(m_Shape);
		m_TargetPoint = GetMiddle(m_Shape);
	}
}

void Spaceship::SetHorVelocity(float speed)
{
	float maxSpeed{ 200 };
	float minSpeed{ -200 };
	m_Velocity.x += speed;
	if (m_Velocity.x >= maxSpeed)
	{
		m_Velocity.x = maxSpeed;
	}
	if (m_Velocity.x <= minSpeed)
	{
		m_Velocity.x = minSpeed;
	}
}

void Spaceship::SetVertVelocity(float speed)
{
	float maxSpeed{ 200 };
	float minSpeed{ -200 };
	m_Velocity.y += speed;
	if (m_Velocity.y >= maxSpeed)
	{
		m_Velocity.y = maxSpeed;
	}
	if (m_Velocity.y <= minSpeed)
	{
		m_Velocity.y = minSpeed;
	}
}

const Vector2f Spaceship::GetCurrentVelocity()
{
	return m_Velocity;
}

const Rectf Spaceship::GetShape()
{
	return m_Shape;
}

const bool Spaceship::IsHit(const Circlef& asteroidShape)
{
	if (m_IsInvincible)
	{
		return false;
	}
	Circlef m_ShapeshipCenterCircle{ GetMiddle(m_Shape).x,GetMiddle(m_Shape).y,10 };
	if (IsOverlapping(m_ShapeshipCenterCircle, asteroidShape) && m_pHealth->GetHealth() > 0)
	{
		m_Shape.bottom = m_CenterPoint.y - m_Shape.height / 2.f;
		m_Shape.left = m_CenterPoint.x - m_Shape.width / 2.f;
		m_IsInvincible = true;
		m_pHealth->TakeDamage(1);
		DeleteTexture(m_HealthText);
		TextureFromString(m_pHealth->ToString(), "Resources/DIN-Light.otf", 50, Color4f{ 1,1,1,1 }, m_HealthText);
		std::cout << m_pHealth->ToString();
		return true;
	}
	return false;
}

const bool Spaceship::IsRocketHit(const Circlef& asteroidShape)
{
	if (IsOverlapping(m_Rocket, asteroidShape))
	{
		m_Rocket.center = GetMiddle(m_Shape);
		m_TargetPoint = GetMiddle(m_Shape);
		m_IsShooting = false;
		return true;
	}
	return false;
}

const bool Spaceship::GetInvincible()
{
	return m_IsInvincible;
}

const bool Spaceship::IsDead()
{
	return m_pHealth->GetHealth() <= 0;
}

void Spaceship::SetBulletTarget(const Point2f& position)
{
	if (!m_IsShooting)
	{
		m_TargetPoint = position;
	}
	m_IsShooting = true;
}

void Spaceship::SetZeroVelocity()
{
	m_Velocity = Vector2f{ 0,0 };
}

void Spaceship::UpdateBottom(float windowHeight)
{
	if (m_Shape.bottom > windowHeight)
	{
		m_Shape.bottom = 0;
	}
	else if (m_Shape.bottom < 0)
	{
		m_Shape.bottom = windowHeight;
	}
}

void Spaceship::UpdateLeft(float windowWidth)
{
	if (m_Shape.left > windowWidth)
	{
		m_Shape.left = 0;
	}
	else if (m_Shape.left < 0)
	{
		m_Shape.left = windowWidth;
	}
}

void Spaceship::UpdateRocket(float elapsedSec)
{
	const float speed{ 10.f };
	Vector2f direction{};
	direction.x = m_TargetPoint.x - m_Rocket.center.x;
	direction.y = m_TargetPoint.y - m_Rocket.center.y;
	m_Rocket.center.x += (direction.x * speed) * elapsedSec;
	m_Rocket.center.y += (direction.y * speed) * elapsedSec;
	if (IsOverlapping(m_Rocket, Circlef{ m_TargetPoint,10.f }))
	{
		m_Rocket.center = GetMiddle(m_Shape);
		m_TargetPoint = GetMiddle(m_Shape);
		m_IsShooting = false;
	}
}
