#include "pch.h"
#include "Tile.h"
#include <iostream>
#include "Texture.h"
#include <algorithm>

Tile::Tile(const Rectf& positionRect, int index)
	:m_Index{index}
	,m_pTexture{nullptr}
	,m_Shape{positionRect}
{
	std::string path{ "Resources/PathTile" };
	if (m_Index < 10)
	{
		path += std::to_string(0);
	}
	path += std::to_string(m_Index) + ".png";
	std::cout << path << std::endl;
	m_pTexture = new Texture{ path };
}

Tile::~Tile()
{
	delete m_pTexture;
}

void Tile::Draw() const
{
	m_pTexture->Draw(m_Shape);
}

int Tile::GetIndex() const
{
	return m_Index;
}

Rectf Tile::GetShape() const
{
	return m_Shape;
}
