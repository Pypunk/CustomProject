#pragma once
#include "Unit.h"
#include "Buidling.h"
class Villager :
    public Unit
{
public:
    Villager(const Point2f position);
    void UpdateBuildingLocation(const Point2f position, const std::vector<std::unique_ptr<GameObject>>& objects);
    std::unique_ptr<Building> PlaceBuilding(ResourceCost& playerResources);
    void GatherResource(ResourceCost& resources);
    void DrawExtra() const override;
    void ToggleBuildMode(bool value);
    bool IsInBuildMode();

    Unit::UnitType GetUnitType() const override;
    void SetPlannedBuilding(Building::BuildingType type);
    std::unique_ptr<Building> CreateBuildingByType(Building::BuildingType type, const Point2f& position);
private:
    bool m_IsInBuildMode;
    bool m_CanPlace;
    std::unique_ptr<Building> m_tempBuilding;
};

