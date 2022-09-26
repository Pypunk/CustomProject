#include "pch.h"
#include "Machine.h"
#include "CircularTimer.h"
#include "Texture.h"

Machine::Machine(const Point2f& position, float size, int time, int price)
	:m_IsActive{ false }
	, m_pTimer{ new CircularTimer{position,time,size} }
	, m_AmountToCollect{ 0 }
	, m_Price{ price }
	, m_Shape{ Point2f{position.x - size * 2.f,position.y - size * 2.f},size * 4.f,size * 4.f }
{
	m_UpgradeButton.SetBottomLeft(m_Shape.GetTopLeft(0.f, -size));
	m_UpgradeButton.width = size;
	m_UpgradeButton.height = size;
}

Machine::~Machine()
{
	delete m_pTimer;
}

void Machine::Update(float elapsedSec)
{
	if (m_IsActive)
	{
		if (m_AmountToCollect < 3)
		{
			m_pTimer->Update(elapsedSec);
			if (m_pTimer->HasTimerRunOut())
			{
				m_AmountToCollect++;
				m_pTimer->Reset();
			}
		}
	}
}

void Machine::Draw() const
{
	Point2f position{ m_Shape.GetBottomLeft() };
	if (m_IsActive)
	{
		Texture text{ "Resources/Images/MachineBase.png" };
		text.Draw(position);
		m_pTimer->Draw();
	}
	else
	{
		Texture text{ "Resources/Images/MachineBaseBronze.png" };
		text.Draw(position);
	}
	utils::DrawRect(m_Shape);
	utils::DrawRect(m_UpgradeButton);
	for (int i{}; i < m_AmountToCollect; ++i)
	{
		utils::DrawRect(Rectf{ position,m_Shape.width/4.f,m_Shape.height/4.f });
		position.x += m_Shape.width/4.f + m_Shape.width/8.f;
	}
}

bool Machine::IsHitByWorker(const Rectf& rect)
{
	if (utils::IsOverlapping(m_Shape, rect))
	{
		m_pTimer->Reset();
		m_AmountToCollect = 0;
		return true;
	}
	return false;
}

bool Machine::IsMachineFull() const
{
	return m_AmountToCollect >= 3;
}

Rectf Machine::GetShape() const
{
	return m_Shape;
}

void Machine::SetActive(const Point2f& mousePos, int& price)
{
	if ((utils::IsPointInRect(mousePos, m_Shape) && !m_IsActive) && price >= m_Price)
	{
		m_IsActive = true;
		price -= m_Price;
		m_Price++;
	}
}

void Machine::UpgradeMachine(const Point2f& mousePos, int& price)
{
	if (utils::IsPointInRect(mousePos, m_UpgradeButton) && price >= m_Price)
	{
		if (m_pTimer->GetMaxSeconds() > 2)
		{
			m_pTimer->UpdateMaxSeconds(m_pTimer->GetMaxSeconds() - 1);
			price -= m_Price;
			m_Price++;
		}
	}
}
