#pragma once
#include "Buidling.h"
class Barracks :
    public Building
{
public:
    Barracks(const Point2f& position);

    BuildingType GetBuildingType() const override;
    ResourceCost GetCost() const override;
};

