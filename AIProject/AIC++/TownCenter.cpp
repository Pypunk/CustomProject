#include "pch.h"
#include "TownCenter.h"

TownCenter::TownCenter(const Point2f& position)
	:Building(position)
{
	m_ProductionSpeed = 10.f;
}

Building::BuildingType TownCenter::GetBuildingType() const
{
	return BuildingType::TownCenter;
}

ResourceCost TownCenter::GetCost() const
{
	return ResourceCost{ 200,150,0 };
}
