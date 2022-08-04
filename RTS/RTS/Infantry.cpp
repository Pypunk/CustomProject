#include "pch.h"
#include "Infantry.h"

Infantry::Infantry(const Point2f& position, float size)
	:Unit{position,size}
{
	m_Color = Color4f{ 1,0,0,1 };
	m_Text = Texture{ "Infantry","Fonts/Pineapple Days.otf",20,Color4f{} };
}
