#include "pch.h"
#include "Villager.h"

Villager::Villager(const Point2f& position, float size)
	:Unit(position,size)
	,m_Color{0,0,0,1}
{
}

const void Villager::Draw()
{
	SetColor(m_Color);
	Unit::Draw();
}
