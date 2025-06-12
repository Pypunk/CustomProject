#include "pch.h"
#include "Villager.h"
#include "AllBuildings.h"
#include <iostream>

Villager::Villager(const Point2f position)
	:Unit(position)
	, m_IsInBuildMode{ false }
	, m_CanPlace{ false }
{
}

void Villager::UpdateBuildingLocation(const Point2f position, const std::vector<std::unique_ptr<GameObject>>& objects)
{
	if (!m_tempBuilding)
	{
		std::cout << "[Debug] Attempted to update null TempBuilding\n";
		m_IsInBuildMode = false;
		return;
	}
	if (m_tempBuilding)
	{
		m_tempBuilding->SetCenter(position);
		m_CanPlace = true;

		for (const auto& obj : objects)
		{
			if (!obj) continue;

			if (m_tempBuilding && utils::IsOverlapping(m_tempBuilding->GetShape(), obj->GetShape()))
			{
				m_CanPlace = false;
				break;
			}
		}
	}
}

std::unique_ptr<Building> Villager::PlaceBuilding(ResourceCost& playerResources)
{
	if (!m_tempBuilding) return nullptr;

	auto cost = m_tempBuilding->GetCost();
	if (!cost.CanAfford(playerResources))
	{
		std::cout << "Not enough resources to place building!\n";
		m_IsInBuildMode = false;
		m_tempBuilding = nullptr;
		return nullptr;
	}

	m_IsInBuildMode = false;
	cost.DeductFrom(playerResources);
	playerResources.Print();

	std::unique_ptr<Building> toPlace = std::move(m_tempBuilding);
	m_tempBuilding = nullptr;
	return toPlace;
}

void Villager::GatherResource(ResourceCost& resources)
{
}

void Villager::DrawExtra() const
{
	Unit::DrawExtra();
	if (m_IsInBuildMode && IsSelected())
	{
		if (m_CanPlace)
			utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 0.5f }); // Green if valid
		else
			utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 0.5f }); // Red if overlapping
		if (m_tempBuilding)
		{
			m_tempBuilding->Draw();
		}
	}
}

void Villager::ToggleBuildMode(bool value)
{
	m_IsInBuildMode = value;
}

bool Villager::IsInBuildMode()
{
	return m_IsInBuildMode;
}

Unit::UnitType Villager::GetUnitType() const
{
	return Unit::UnitType::Villager;
}

void Villager::SetPlannedBuilding(Building::BuildingType type)
{
	switch (type)
	{
	case Building::BuildingType::TownCenter:
		m_tempBuilding = std::make_unique<TownCenter>(Point2f{});
		break;
	case Building::BuildingType::Barracks:
		m_tempBuilding = std::make_unique<Barracks>(Point2f{});
		break;
	case Building::BuildingType::ArcheryRange:
		m_tempBuilding = std::make_unique<ArcheryRange>(Point2f{});
		break;
	case Building::BuildingType::Stables:
		m_tempBuilding = std::make_unique<Stables>(Point2f{});
		break;
	default:
		break;
	}
}

std::unique_ptr<Building> Villager::CreateBuildingByType(Building::BuildingType type, const Point2f& position)
{
	switch (type)
	{
	case Building::BuildingType::TownCenter:
		std::cout << "TownCenter Created\n";
		return std::make_unique<TownCenter>(position);
	case Building::BuildingType::Barracks:
		std::cout << "Barracks Created\n";
		return std::make_unique<Barracks>(position);
	case Building::BuildingType::ArcheryRange:
		std::cout << "Archery Range Created \n";
		return std::make_unique<ArcheryRange>(position);
	case Building::BuildingType::Stables:
		std::cout << "Stables Created\n";
		return std::make_unique<Stables>(position);
	default:
		return nullptr;
	}
	return nullptr;
}
