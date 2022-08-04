#include "pch.h"
#include "Villager.h"

Villager::Villager(const Point2f& position, float size)
	:Unit(position,size)
{
	m_Text = Texture{ "Villager","Fonts/Pineapple Days.otf",20,Color4f{} };
}
