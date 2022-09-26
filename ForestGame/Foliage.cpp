#include "pch.h"
#include "Foliage.h"
#include "Texture.h"

Foliage::Foliage(const Point2f& position, int typeId)
	:GameObject{position}
	,m_CurrentType{Type{typeId}}
	,m_Angle{}
	,m_IsShaking{false}
	, isRotatingLeft{true}
{
	const float scale{ 3.f };
	const int amountOfTypes{ 3 };
	const int amountOfTreesPerType{ 4 };
	std::string path{};
	switch (m_CurrentType)
	{
	case Type::Tree:
		path = "Resources/Textures/Forest/Trees/";
		path += "Tree-" + std::to_string(utils::GetRand(1, amountOfTypes));
		path += "-" + std::to_string(utils::GetRand(1, amountOfTreesPerType)) + ".png";
		m_IsPassable = false;
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

void Foliage::Update(float elapsedSec)
{
	if (m_CurrentType != Type::Tree)
	{
		if (m_IsShaking)
		{
			if (isRotatingLeft)
			{
				m_Angle += 60 * elapsedSec;
				m_Counter += elapsedSec;
				if (0.2 < m_Counter)
				{
					m_Counter = 0.f;
					isRotatingLeft = false;
				}
			}
			else
			{
				m_Angle -= 60 * elapsedSec;
				m_Counter += elapsedSec;
				if (0.2 < m_Counter)
				{
					m_Counter = 0.f;
					isRotatingLeft = true;
					m_IsShaking = false;
				}
			}
		}
		else
		{
			m_Angle = 0.f;
		}
	}
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

void Foliage::SetToShaking(const Rectf& rect)
{
	if (utils::IsOverlapping(GetCollisionShape(), rect))
	{
		m_IsShaking = true;
	}
}
