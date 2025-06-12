#pragma once
#include "Buidling.h"
class ArcheryRange :
    public Building
{
public:
    ArcheryRange(const Point2f& position);

    BuildingType GetBuildingType() const override;
    ResourceCost GetCost() const override;
};

