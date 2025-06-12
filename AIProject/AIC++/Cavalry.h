#pragma once
#include "Unit.h"
class Cavalry :
    public Unit
{
public:
    Cavalry(const Point2f& position);

    Unit::UnitType GetUnitType() const override;
};

