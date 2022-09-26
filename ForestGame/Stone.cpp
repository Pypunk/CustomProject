#include "pch.h"
#include "Stone.h"
#include "Texture.h"

Stone::Stone(const Point2f& position)
	:GameObject{position}
{
	float scale{ 3.f };
	const int amountOfTypes{ 2 };
	std::string path{ "Resources/Textures/Forest/Stones/" };
	path += "Stone-" + std::to_string(utils::GetRand(1, amountOfTypes)) + ".png";
	m_pTexture = new Texture{ path };
	m_Shape.width = m_pTexture->GetWidth() * scale;
	m_Shape.height = m_pTexture->GetHeight() * scale;
	m_IsPassable = false;
}
