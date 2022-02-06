#include "pch.h"
#include "Tile.h"
#include "Texture.h"
#include "utils.h"
#include <string>
#include <iostream>
using namespace utils;
Tile::Tile(const Point2f& position)
	:m_Position{position}
	,m_IsPrevSpike{false}
{
	textureStrings.push_back("Resources/Grass.png");
	textureStrings.push_back("Resources/Spikes.png");
	CreateRandomTexture();
}

Tile::Tile(const Tile& tile)
	:m_Position{tile.m_Position}
	,m_IsPrevSpike{tile.m_IsPrevSpike}
{
	for (int i{}; i < m_AmountOfTextures; ++i)
	{
		textureStrings[i] = tile.textureStrings[i];
	}
	m_pTexture = tile.m_pTexture;
	m_IsSpike = tile.m_IsSpike;
}

Tile::Tile(Tile&& tile) noexcept
	:m_Position{tile.m_Position}
	,m_IsPrevSpike{tile.m_IsPrevSpike}
{
	for (int i{}; i < m_AmountOfTextures; ++i)
	{
		textureStrings[i] = tile.textureStrings[i];
	}
	m_pTexture = tile.m_pTexture;
	m_IsSpike = tile.m_IsSpike;
	delete tile.m_pTexture;
	tile.m_pTexture = nullptr;
}

Tile::~Tile()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

const void Tile::Draw()
{
	m_pTexture->Draw(m_Position);
}

const Rectf Tile::GetShape()
{
	return Rectf{ m_Position.x,m_Position.y,m_pTexture->GetWidth(),m_pTexture->GetHeight() };
}

bool Tile::IsSpike()
{
	return m_IsSpike;
}

void Tile::DetectPreviousTile(Tile* previous)
{
	if (previous->IsSpike())
	{
		delete m_pTexture;
		m_pTexture = nullptr;
		m_pTexture = new Texture{ "Resources/Grass.png" };
		m_IsSpike = false;
	}
}

void Tile::CreateRandomTexture()
{
	std::string randString{ textureStrings[GetRand(0,m_AmountOfTextures)] };
	m_pTexture = new Texture{ randString };
	if (randString == "Resources/Spikes.png")
	{
		m_IsSpike = true;
	}
	else
	{
		m_IsSpike = false;
	}
}

void Tile::Update(float elapsedSec, float amountOfTiles)
{
	m_Position.x -= 200.f * elapsedSec;
	if (m_Position.x+m_pTexture->GetWidth() < 0)
	{
		m_Position.x += m_pTexture->GetWidth() * amountOfTiles;
		delete m_pTexture;
		m_pTexture = nullptr;
		CreateRandomTexture();
	}
}
