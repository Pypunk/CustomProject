#include "pch.h"
#include "Foliage.h"
#include "Texture.h"

Foliage::Foliage(const Point2f& position, int typeId)
	:GameObject{position}
	,m_CurrentType{Type{typeId}}
	,m_Angle{}
{
	const float scale{ 3.f };
	int randNr{utils::GetRand(1,3)};

	switch (m_CurrentType)
	{
	case Type::Tree:
		if (randNr >= 2)
		{
			m_IsPassable = false;
		}
		break;
	}
	m_pTexture = std::make_unique<Texture>( GenerateImagePath(m_CurrentType,randNr) );
	m_Shape.width = m_pTexture->GetWidth() * scale;
	m_Shape.height = m_pTexture->GetHeight() * scale;
}

Foliage::~Foliage()
{
}

void Foliage::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Shape.GetCenter().x, m_Shape.GetCenter().y, 0.f);
	glRotatef(m_Angle, 0.f, 0.f, 1.f);
	glTranslatef(-m_Shape.GetCenter().x, -m_Shape.GetCenter().y, 0.f);
	GameObject::Draw();
	glPopMatrix();
}

std::string Foliage::GenerateImagePath(Type type, int randNr) const
{
	std::string path{};
	const int amountOfTypes{ 3 };
	const int amountOfTreesPerType{ 4 };
	switch (m_CurrentType)
	{
	case Type::Tree:
		path = "Resources/Textures/Forest/Trees/";
		path += "Tree-" + std::to_string(randNr);
		randNr = utils::GetRand(1, amountOfTreesPerType);
		path += "-" + std::to_string(randNr) + ".png";
		break;
	case Type::Bush:
		path = "Resources/Textures/Forest/Bushes/";
		path += "Bush-" + std::to_string(randNr + 1);
		path += ".png";
		break;
	case Type::Flower:
		path = "Resources/Textures/Forest/Flowers/";
		path += "Flower-" + std::to_string(randNr);
		path += ".png";
		break;
	}
	return path;
}
