#include "pch.h"
#include "ArcheryRange.h"

ArcheryRange::ArcheryRange(const Point2f& position)
	:Building(position)
{
	m_Shape.width = 80.f;
	m_Shape.height = 80.f;
	m_ProgressBar.width = m_Shape.width;
	m_CurrentHealth.width = m_Shape.width;
	m_MaxHealth.width = m_Shape.width;
	m_MaxHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_CurrentHealth.bottom = m_Shape.GetTopLeft(0.f, 10.f).y;
	m_ProductionSpeed = 8.f;
}

Building::BuildingType ArcheryRange::GetBuildingType() const
{
	return BuildingType::ArcheryRange;
}

ResourceCost ArcheryRange::GetCost() const
{
	return ResourceCost(0, 100, 100);
}
