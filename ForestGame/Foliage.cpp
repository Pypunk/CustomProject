#include "pch.h"
#include "Foliage.h"
#include "Texture.h"

Foliage::Foliage(const Point2f& position, int typeId)
	:GameObject{position}
	,m_CurrentType{Type{typeId}}
	,m_Angle{}
{
	const float scale{ 3.f };
	const int amountOfTypes{ 3 };
	const int amountOfTreesPerType{ 4 };
	std::string path{};
	int randNr{};
	switch (m_CurrentType)
	{
	case Type::Tree:
		path = "Resources/Textures/Forest/Trees/";
		path += "Tree-" + std::to_string(utils::GetRand(1, amountOfTypes));
		randNr = utils::GetRand(1, amountOfTreesPerType);
		path += "-" + std::to_string(randNr) + ".png";
		m_IsPassable = true;
		if (randNr >= 2)
		{
			m_IsPassable = false;
		}
		break;
	case Type::Bush:
		path = "Resources/Textures/Forest/Bushes/";
		path += "Bush-" + std::to_string(utils::GetRand(1,amountOfTypes+1));
		path += ".png";
		m_IsPassable = true;
		break;
	case Type::Flower:
		path = "Resources/Textures/Forest/Flowers/";
		path += "Flower-" + std::to_string(utils::GetRand(1, amountOfTypes));
		path += ".png";
		m_IsPassable = true;
		break;
	}
	m_pTexture = new Texture{ path };
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
