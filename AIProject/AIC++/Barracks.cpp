#include "pch.h"
#include "Barracks.h"

Barracks::Barracks(const Point2f& position)
	:Building(position)
{
	m_Shape.width = 50.f;
	m_Shape.height = 80.f;
	m_ProgressBar.width = m_Shape.width;
	m_CurrentHealth.width = m_Shape.width;
	m_MaxHealth.width = m_Shape.width;
	m_MaxHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_CurrentHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_ProductionSpeed = 5.f;
}

Building::BuildingType Barracks::GetBuildingType() const
{
	return BuildingType::Barracks;
}

ResourceCost Barracks::GetCost() const
{
	return ResourceCost{ 50,100,50 };
}
