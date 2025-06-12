#pragma once
#include "Unit.h"
class Infantry :
    public Unit
{
public:
    Infantry(const Point2f position);



    Unit::UnitType GetUnitType() const override;
};

