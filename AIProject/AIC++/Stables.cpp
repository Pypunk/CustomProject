#include "pch.h"
#include "Stables.h"

Stables::Stables(const Point2f& position)
	:Building(position)
{
	m_Shape.width = 50.f;
	m_Shape.height = 50.f;
	m_ProgressBar.width = m_Shape.width;
	m_CurrentHealth.width = m_Shape.width;
	m_MaxHealth.width = m_Shape.width;
	m_MaxHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_CurrentHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_ProductionSpeed = 5.f;
}

Building::BuildingType Stables::GetBuildingType() const
{
	return BuildingType::Stables;
}

ResourceCost Stables::GetCost() const
{
	return ResourceCost(100, 150, 100);
}
