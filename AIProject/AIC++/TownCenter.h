#pragma once
#include "Buidling.h"
class TownCenter :
    public Building
{
public:
    TownCenter(const Point2f& position);

    BuildingType GetBuildingType() const override;
    ResourceCost GetCost() const override;
};

