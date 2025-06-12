#pragma once
#include "Unit.h"
class Ranged : public Unit
{
public:
	Ranged(const Point2f& position);

	Unit::UnitType GetUnitType() const override;
};

