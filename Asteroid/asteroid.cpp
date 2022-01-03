#include "pch.h"
#include "asteroid.h"
#include "utils.h"
#include <iostream>
#include "Spaceship.h"

Asteroid::Asteroid(const Point2f& position, float radius, Spaceship* ship)
	:m_Shape(position,radius)
	,m_Texture{}
{
	const int maxSpeed{ 200 };
	TextureFromFile("Resources/Asteroid.png", m_Texture);
	m_Velocity.x = SetRandXVelocity(maxSpeed, ship);
	m_Velocity.y = SetRandYVelocity(maxSpeed, ship);
}

Asteroid::~Asteroid()
{
	DeleteTexture(m_Texture);
}

void Asteroid::Draw()
{
	const float radiusOffSet{ 5.f };
	Rectf textureRect{};
	textureRect.bottom = m_Shape.center.y - m_Shape.radius-radiusOffSet/2.f;
	textureRect.left = m_Shape.center.x - m_Shape.radius-radiusOffSet/2.f;
	textureRect.width = m_Shape.radius*2.f+radiusOffSet;
	textureRect.height = textureRect.width;
	DrawTexture(m_Texture, textureRect);
}

void Asteroid::Update(float elapsedSec)
{
	m_Shape.center.x += m_Velocity.x * elapsedSec;
	m_Shape.center.y += m_Velocity.y * elapsedSec;
}

const Circlef Asteroid::GetShape()
{
	return m_Shape;
}

const Vector2f Asteroid::GetVelocity()
{
	return m_Velocity;
}

float Asteroid::SetRandXVelocity(int maxSpeed, Spaceship* ship)
{
	if (ship->GetShape().left < m_Shape.center.x)
	{
		return -float(rand() % maxSpeed);
	}
	else if (ship->GetShape().left > m_Shape.center.x)
	{
		return float(rand() % maxSpeed);
	}
	return 0;
}

float Asteroid::SetRandYVelocity(int maxSpeed, Spaceship* ship)
{
	if (ship->GetShape().bottom < m_Shape.center.y)
	{
		return -float(rand() % maxSpeed);
	}
	else if (ship->GetShape().bottom > m_Shape.center.y)
	{
		return float(rand() % maxSpeed);
	}
	return 0;
}
