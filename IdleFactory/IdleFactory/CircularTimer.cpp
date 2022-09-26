#include "pch.h"
#include "CircularTimer.h"
#include <iostream>
#include "TextureManager.h"

CircularTimer::CircularTimer(const Point2f& position,int seconds, float size)
	: m_Position{position}
	, m_Angle{ utils::g_Pi }
	, m_Seconds{ seconds }
	, m_Interval{ 0 }
	, m_SecondsText{ float(seconds) }
	, m_Size{size}
	, m_Circle{ position,size }
{
}

CircularTimer::~CircularTimer()
{
}

CircularTimer::CircularTimer(const CircularTimer& other)
	: m_Position{ other.m_Position }
	, m_Angle{ other.m_Angle }
	, m_Seconds{ other.m_Seconds }
	, m_Interval{ other.m_Interval }
	, m_SecondsText{ other.m_SecondsText }
	, m_Size{ other.m_Size }
	, m_Circle{ other.m_Circle }
{
}

CircularTimer::CircularTimer(CircularTimer&& other) noexcept
	: m_Position{ other.m_Position }
	, m_Angle{ other.m_Angle }
	, m_Seconds{ other.m_Seconds }
	, m_Interval{ other.m_Interval }
	, m_SecondsText{ other.m_SecondsText }
	, m_Size{ other.m_Size }
	, m_Circle{ other.m_Circle }
{
}

CircularTimer& CircularTimer::operator=(const CircularTimer& other)
{
	// TODO: insert return statement here
	m_Position = other.m_Position;
	m_Angle = other.m_Angle;
	m_Seconds = other.m_Seconds;
	m_Interval = other.m_Interval;
	m_SecondsText = other.m_SecondsText;
	m_Size = other.m_Size;
	m_Circle = other.m_Circle;

	return *this;
}

CircularTimer& CircularTimer::operator=(CircularTimer&& other) noexcept
{
	// TODO: insert return statement here
	m_Position = other.m_Position;
	m_Angle = other.m_Angle;
	m_Seconds = other.m_Seconds;
	m_Interval = other.m_Interval;
	m_SecondsText = other.m_SecondsText;
	m_Size = other.m_Size;
	m_Circle = other.m_Circle;

	return *this;
}

void CircularTimer::Update(float elapsedSec)
{
	if (!HasTimerRunOut())
	{
		m_Interval += elapsedSec;
		if (0.1f < m_Interval)
		{
			m_Angle -= utils::g_Pi / (m_Seconds / 2.f) * 0.1f;
			m_SecondsText -= 0.1f;
			m_Interval = 0.f;
		}
	}
}

void CircularTimer::Draw() const
{
	TextureManager& textureManager(TextureManager::GetInstance());
	utils::SetColor(Color4f{ 0,0.6f,0,1 });
	utils::FillArc(m_Position, m_Size, m_Size, -utils::g_Pi, m_Angle);
	utils::SetColor(Color4f{ 1,1,1,1 });
	utils::DrawCircle(m_Circle, 5.f);
	textureManager.DrawFont(std::to_string(int(m_SecondsText)), "Pineapple Days.otf", int(m_Size), Color4f{1,1,1,1}, m_Circle.center);
}

void CircularTimer::Reset()
{
	m_Angle = utils::g_Pi;
	m_SecondsText = float(m_Seconds);
}

bool CircularTimer::HasTimerRunOut() const
{
	return int(m_SecondsText) == 0.f;
}

void CircularTimer::UpdateMaxSeconds(int seconds)
{
	m_Seconds = seconds;
	Reset();
}

int CircularTimer::GetMaxSeconds() const
{
	return m_Seconds;
}
