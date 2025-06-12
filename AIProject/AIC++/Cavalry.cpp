#include "pch.h"
#include "Cavalry.h"

Cavalry::Cavalry(const Point2f& position)
	:Unit(position)
{
}

Unit::UnitType Cavalry::GetUnitType() const
{
	return Unit::UnitType::Cavalry;
}
