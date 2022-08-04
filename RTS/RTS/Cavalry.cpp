#include "pch.h"
#include "Cavalry.h"

Cavalry::Cavalry(const Point2f& position, float size)
	:Unit(position,size)
{
	m_Color = Color4f{ 1,1,0,1 };
	m_Text = Texture{ "Cavalry","Fonts/Pineapple Days.otf",20,Color4f{} };
}
