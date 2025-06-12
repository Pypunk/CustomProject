#include "pch.h"
#include "Infantry.h"

Infantry::Infantry(const Point2f position)
	:Unit(position)
{
}

Unit::UnitType Infantry::GetUnitType() const
{
	return Unit::UnitType::Infantry;
}
