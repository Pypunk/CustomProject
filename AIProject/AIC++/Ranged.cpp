#include "pch.h"
#include "Ranged.h"

Ranged::Ranged(const Point2f& position)
	:Unit(position)
{
}

Unit::UnitType Ranged::GetUnitType() const
{
	return Unit::UnitType::Ranged;
}
