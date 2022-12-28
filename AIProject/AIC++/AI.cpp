#include "pch.h"
#include "AI.h"
#include <cmath>
#include <iostream>
#include "PatrolPoints.h"

AI::AI(const Point2f& position)
	:m_Shape(position,50,50)
	, m_Angle{}
	, m_WalkSpeed{ 100.f }
{
	m_ForwardVector = m_Shape.GetCenterRight() - m_Shape.GetCenterRight(-m_Shape.width);
}

void AI::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Shape.GetCenter().x, m_Shape.GetCenter().y, 0.f);
	glRotatef(m_Angle, 0.f, 0.f, 1.f);
	glTranslatef(-m_Shape.GetCenter().x, -m_Shape.GetCenter().y, 0.f);
	utils::DrawRect(m_Shape);
	utils::DrawVector(m_Shape.GetCenter(), m_ForwardVector);
	glPopMatrix();
}

void AI::Face(const Point2f& target, float elapsedSec)
{
	Vector2f direction{m_Shape.GetCenter(),target};
	float dotproduct = direction.DotProduct(m_ForwardVector);
	float amplitudeOfBothVectorsMultiplied{ m_ForwardVector.Length() * direction.Length() };
	m_Angle = utils::ConvertToDegrees(acosf(dotproduct / amplitudeOfBothVectorsMultiplied));
	if (target.y < m_Shape.GetCenter().y)
	{
		m_Angle = -m_Angle;
	}
}

void AI::Follow(const Point2f& target, float elapsedSec)
{
	Face(target, elapsedSec);
	Vector2f direction{ m_Shape.GetCenter(),target };
	direction = direction.Normalized();
	direction *= 100.f;
	m_Shape.left += direction.x * elapsedSec;
	m_Shape.bottom += direction.y * elapsedSec;
}

void AI::Evade(const Point2f& target, float elapsedSec)
{
	Vector2f direction{ m_Shape.GetCenter(),target };
	float dotproduct = direction.DotProduct(m_ForwardVector);
	float amplitudeOfBothVectorsMultiplied{ m_ForwardVector.Length() * direction.Length() };
	m_Angle = utils::ConvertToDegrees(acosf(-dotproduct / amplitudeOfBothVectorsMultiplied));
	if (target.y > m_Shape.GetCenter().y)
	{
		m_Angle = -m_Angle;
	}
	if (utils::GetDistance(m_Shape.GetCenter(), target) <= 300.f)
	{
		direction = direction.Normalized();
		direction *= 100.f;
		m_Shape.left -= direction.x * elapsedSec;
		m_Shape.bottom -= direction.y * elapsedSec;
	}
}

void AI::Patrol(PatrolPoints& points, float elapsedSec)
{
	if (!points.isEmpty())
	{
		if (points.size() > 1)
		{
			if (utils::GetDistance(points[counter], m_Shape.GetCenter()) < 10.f)
			{
				counter++;
				std::cout << counter << std::endl;
				if (counter == points.size())
				{
					counter = 0;
				}
			}
		}
		else
		{
			counter = 0;
		}
		Follow(points[counter], elapsedSec);
	}
}
