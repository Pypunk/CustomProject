#include "pch.h"
#include "Character.h"
#include <iostream>
#include "TextureManager.h"
#include "Machine.h"

Character::Character(const Window& window)
: m_Shape{ Point2f{window.width / 2.f - 25.f,25.f},50.f,50.f }
, m_Target{}
, m_Currency{ 0 }
,m_TargetSet{false}
,m_IsMoving{false}
{
	m_StartPos = m_Shape.GetCenter();
}

void Character::Update(float elapsedSec, Machine* pMachine)
{
	Vector2f vector{};
	if (pMachine->IsMachineFull())
	{
		if (!m_TargetSet)
		{
			m_TargetSet = true;
		}
		else
		{
			if (!m_IsMoving)
			{
				m_Target = pMachine->GetShape().GetCenter();
				m_IsMoving = true;
			}
			vector = Vector2f{ m_Shape.GetCenter(),m_Target };
			if (pMachine->IsHitByWorker(m_Shape))
			{
				m_Currency += 3;
				m_IsMoving = false;
				m_TargetSet = false;
			}
		}
	}
	else
	{
		if (!m_TargetSet)
		{
			vector = Vector2f{ m_Shape.GetCenter(),m_StartPos };
		}
	}
	m_Shape.bottom += vector.y * elapsedSec;
	m_Shape.left += vector.x * elapsedSec;
}

void Character::Draw() const
{
	utils::DrawRect(m_Shape);
	TextureManager& textureManager(TextureManager::GetInstance());
	textureManager.DrawFont(std::to_string(m_Currency), "Pineapple Days.otf", int(m_Shape.width), Color4f{ 1,1,1,1 }, Point2f{});
}

int& Character::GetCurrency()
{
	return m_Currency;
}
