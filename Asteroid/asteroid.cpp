#include "pch.h"
#include "asteroid.h"
#include "utils.h"
#include <iostream>
#include "Spaceship.h"

Asteroid::Asteroid(const Point2f& position, Spaceship* ship)
	:m_Position(position)
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
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, 0.f);
	glRotatef(m_Angle, 0, 0, 1);
	glScalef(0.7f, 0.7f, 1.f);
	Rectf textureRect{ 0,0,m_Texture.width,m_Texture.height };
	DrawTexture(m_Texture, Point2f{ -GetMiddle(textureRect).x,-GetMiddle(textureRect).y });
	glPopMatrix();
}

void Asteroid::Update(float elapsedSec)
{
	m_Angle++;
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
}

const Circlef Asteroid::GetShape()
{
	return Circlef{ m_Position,m_Texture.width / 2.f-10.f };
}

const Vector2f Asteroid::GetVelocity()
{
	return m_Velocity;
}

float Asteroid::SetRandXVelocity(int maxSpeed, Spaceship* ship)
{
	if (ship->GetShape().left < m_Position.x)
	{
		return -float(rand() % maxSpeed);
	}
	else if (ship->GetShape().left > m_Position.x)
	{
		return float(rand() % maxSpeed);
	}
	return 0;
}

float Asteroid::SetRandYVelocity(int maxSpeed, Spaceship* ship)
{
	if (ship->GetShape().bottom < m_Position.y)
	{
		return -float(rand() % maxSpeed);
	}
	else if (ship->GetShape().bottom > m_Position.y)
	{
		return float(rand() % maxSpeed);
	}
	return 0;
}
