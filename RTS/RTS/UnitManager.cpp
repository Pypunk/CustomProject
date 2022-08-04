#include "pch.h"
#include "UnitManager.h"
#include "Unit.h"
#include "Villager.h"
#include "Infantry.h"
#include "Cavalry.h"
#include <iostream>

UnitManager::UnitManager()
	:m_pUnits{}
	,m_AmountSelected{}
{
}

UnitManager::~UnitManager()
{
	for (Unit* i : m_pUnits)
	{
		delete i;
	}
}

void UnitManager::Update(float elapsedSec)
{
	for (Unit* i : m_pUnits)
	{
		i->MoveTo(elapsedSec);
	}
}

void UnitManager::Draw() const
{
	for (const Unit* i : m_pUnits)
	{
		i->Draw();
	}
}

void UnitManager::AddUnit(const Type& type, const Point2f& position)
{
	const float size{50.f};
	switch (type)
	{
	case Type::villager:
		m_pUnits.push_back(new Villager{ position,size });
		break;
	case Type::infantry:
		m_pUnits.push_back(new Infantry{ position,size });
		break;
	case Type::cavalry:
		m_pUnits.push_back(new Cavalry{ position,size });
		break;
	}
}

void UnitManager::SelectUnits(const Point2f& mousePos, const Rectf& selectionRect)
{
	m_SelectedIndexes.clear();
	if (m_pUnits.size() > 0)
	{
		for (int i{}; i <= m_pUnits.size() - 1; ++i)
		{
			m_pUnits[i]->Deselect();
			if (m_pUnits[i]->SelectUnit(mousePos) || m_pUnits[i]->SelectUnit(selectionRect))
			{
				m_SelectedIndexes.push_back(i);
			}
		}
	}
	
}

void UnitManager::CheckAmountSelected()
{
	m_AmountSelected = 0;
	for (int i : m_SelectedIndexes)
	{
		if (i >= 0)
		{
			m_AmountSelected++;
		}
	}
}

void UnitManager::MoveUnits(const Point2f& mousePos)
{
	int cols{};
	int rows{};
	if (m_AmountSelected > 0)
	{
		SetColsAndRows(m_AmountSelected, cols, rows, m_SelectedIndexes, mousePos);
		SetMovePositions(m_AmountSelected, cols, rows, m_MovePositions, m_SelectedIndexes, mousePos);
	}
}

void UnitManager::DoubleClickSelect(const Point2f& mousePos, bool doubleClickDetected, const Rectf& cameraRect)
{
	for (Unit* unit : m_pUnits)
	{
		if (doubleClickDetected && unit->SelectUnit(mousePos))
		{
			m_SelectedIndexes.clear();
			if (typeid(*unit) == typeid(Infantry))
			{
				for (int i{}; i < m_pUnits.size(); i++)
				{
					if (typeid(*m_pUnits[i]) == typeid(Infantry) && utils::IsOverlapping(m_pUnits[i]->GetShape(),cameraRect))
					{
						m_pUnits[i]->Select();
						m_SelectedIndexes.push_back(i);
					}
				}
			}
			if (typeid(*unit) == typeid(Villager))
			{
				for (int i{}; i < m_pUnits.size(); i++)
				{
					if (typeid(*m_pUnits[i]) == typeid(Villager))
					{
						m_pUnits[i]->Select();
						m_SelectedIndexes.push_back(i);
					}
				}
			}
			if (typeid(*unit) == typeid(Cavalry))
			{
				for (int i{}; i < m_pUnits.size(); i++)
				{
					if (typeid(*m_pUnits[i]) == typeid(Cavalry))
					{
						m_pUnits[i]->Select();
						m_SelectedIndexes.push_back(i);
					}
				}
			}
		}
	}
}

void UnitManager::SetColsAndRows(int amount, int& cols, int& rows, std::vector<int>& indexes, const Point2f& mousePos)
{
	if (!(amount % 2))
	{
		cols = 2;
		rows = 1;
		if (!(amount % 4))
		{
			cols = 2;
			rows = 2;
			if (!(amount % 8))
			{
				cols = 4;
				rows = 2;
			}
		}
		if (!(amount % 6))
		{
			cols = 3;
			rows = 2;
		}
		if (!(amount % 10))
		{
			cols = 5;
			rows = 2;
			if (!(amount % 20))
			{
				cols = 5;
				rows = 4;
			}
			if (!(amount % 30))
			{
				cols = 5;
				rows = 6;
			}
		}
	}
	else
	{
		cols = amount;
		if (amount == 1)
		{
			rows = 1;
		}
		else
		{
			rows = amount / 2;
		}
	}
	if (m_pUnits[indexes[amount / 2]]->GetShape().left < mousePos.x - 200.f
		|| m_pUnits[indexes[amount / 2]]->GetShape().left > mousePos.x + 200.f)
	{
		int temp{ rows };
		rows = cols;
		cols = temp;
	}
}

void UnitManager::SetMovePositions(int amount, int& cols, int& rows, std::vector<Point2f>& movePositions, std::vector<int>& indexes, const Point2f& mousePos)
{
	movePositions.clear();
	Point2f currentPos{ mousePos.x - m_pUnits[0]->GetShape().width / 2.f * cols,mousePos.y - m_pUnits[0]->GetShape().height / 2.f };
	const float offSet{20.f};
	for (int i{}; i < rows; ++i)
	{
		for (int j{}; j < cols; ++j)
		{
			movePositions.push_back(currentPos);
			currentPos.x += m_pUnits[0]->GetShape().width + offSet;
		}
		currentPos.x = mousePos.x - m_pUnits[0]->GetShape().width/2.f * cols;
		currentPos.y += m_pUnits[0]->GetShape().height + offSet;
	}

	for (int i{}; i < amount; ++i)
	{
		m_pUnits[indexes[i]]->SetMoveLocation(movePositions[i]);
	}
}
