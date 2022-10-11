#include "pch.h"
#include "Level.h"
#include "GameObject.h"
#include "Foliage.h"
#include "Stone.h"
#include "Player.h"
#include "Portal.h"
#include "Texture.h"
#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Camera.h"
#include "SVGParser.h"
Level::Level()
	:m_IsDebugMode{false}
	,m_pLevelTexture{nullptr}
	,m_IsLevelEnded{false}
{
}

void Level::Update(float elapsedSec)
{
	UpdateGameObjects(elapsedSec);
	std::sort(m_pObjects.begin(), m_pObjects.end(), [](const GameObject* lhs, const GameObject* rhs)
		{
			return lhs->GetShape().bottom > rhs->GetShape().bottom;
		});
}

void Level::Draw(Camera* camera) const
{
	glPushMatrix();
	for (const GameObject* i : m_pObjects)
	{
		if (typeid(*i) == typeid(Player))
		{
			camera->Draw(i->GetShape());
		}
	}
	m_pLevelTexture->Draw(GetLevelShape());
	for (const GameObject* i : m_pObjects)
	{
		i->Draw();
	}
	if (m_IsDebugMode)
	{
		DrawDebugMode();
	}
	glPopMatrix();
}

Rectf Level::GetLevelShape() const
{
	return Rectf{ 0,0,m_pLevelTexture->GetWidth() * 3.f,m_pLevelTexture->GetHeight() * 3.f };
}

void Level::ToggleDebugMode()
{
	m_IsDebugMode = !m_IsDebugMode;
}

Level::~Level()
{
	ClearLevel();
}

void Level::CreateLevelFromFile(const std::string& fileName)
{
	ClearLevel();
	m_IsLevelEnded = false;
	std::ifstream ifs{ fileName };
	std::string object{};
	while (std::getline(ifs, object, '>'))
	{
		CreateObject(object);
	}
	m_pObjects.push_back(new Skeleton{ Point2f{450.f,360.f} });
}

bool Level::IsLevelEnded() const
{
	return m_IsLevelEnded;
}

void Level::CreateObject(const std::string& object)
{
	if (object.find("BackgroundTexture") != std::string::npos)
	{
		CreateBackgroundTexture(object);
	}
	if (object.find("Player") != std::string::npos)
	{
		CreatePlayer(object);
	}
	if (object.find("Foliage") != std::string::npos)
	{
		CreateFoliage(object);
	}
	if (object.find("Stone") != std::string::npos)
	{
		CreateStone(object);
	}
	if (object.find("Portal") != std::string::npos)
	{
		CreatePortal(object);
	}
}

void Level::CreateFoliage(const std::string& foliage)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", foliage));
	int type = ToFoliageTypeId(GetAttributeValue("Type", foliage));

	m_pObjects.push_back(new Foliage{ position,type });
}

void Level::CreateStone(const std::string& stone)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", stone));

	m_pObjects.push_back(new Stone{ position });
}

void Level::CreatePortal(const std::string& portal)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", portal));

	m_pObjects.push_back(new Portal{ position });
}

void Level::CreateBackgroundTexture(const std::string& texture)
{
	std::string path{ "Resources/Textures/Level/" };

	m_pLevelTexture = new Texture{ path + GetAttributeValue("Texture",texture) };
	SVGParser::GetVerticesFromSvgFile(path + GetAttributeValue("SVG", texture), m_Vertices);
}

void Level::CreatePlayer(const std::string& player)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", player));

	m_pObjects.push_back(new Player{ position });
}

Point2f Level::ToPoint2f(const std::string& point2fStr) const
{
	std::stringstream ss{ point2fStr };
	std::string pointString{};
	Point2f point;
	for (int i{}; i < 2; ++i)
	{
		std::getline(ss, pointString, ',');
		switch (i)
		{
		case 0:
			point.x = std::stof(pointString);
			break;
		case 1:
			point.y = std::stof(pointString);
			break;
		}
	}
	return point;
}

int Level::ToFoliageTypeId(const std::string& foliageTypeId) const
{
	if (foliageTypeId == "Tree")
	{
		return 1;
	}
	else if (foliageTypeId == "Bush")
	{
		return 2;
	}
	else
	{
		return 3;
	}

}

std::string Level::GetAttributeValue(const std::string& attrName, const std::string& element) const
{
	std::string attribute;
	size_t start{ element.find(attrName, 0) };
	size_t firstQuote{ element.find("\"", start + attrName.length()) };
	size_t secondQuote{ element.find("\"", firstQuote + 1) };
	size_t substrLength{ secondQuote - firstQuote - 1 };
	attribute = element.substr(firstQuote + 1, substrLength);
	return attribute;
}

void Level::UpdateGameObjects(float elapsedSec)
{
	Player* player{};
	int counter{};
	for (GameObject* i : m_pObjects)
	{
		if (typeid(*i) == typeid(Player))
		{
			Player* newPlayer{ dynamic_cast<Player*>(i) };
			player = newPlayer;
			player->Update(elapsedSec);
			player->DoCollisions(m_Vertices, elapsedSec);
			for (GameObject* j : m_pObjects)
			{
				if (player)
				{
					player->DoCollisions(j,elapsedSec);
				}
			}
		}
		if (typeid(*i) == typeid(Portal))
		{
			Portal* portal{ dynamic_cast<Portal*>(i) };
			if (player)
			{
				if (portal->IsPlayerOverLapping(player))
				{
					m_IsLevelEnded = true;
					player = nullptr;
				}
			}
		}
		if (typeid(*i) == typeid(Skeleton))
		{
			Enemy* enemy{ dynamic_cast<Skeleton*>(i) };
			if (player)
			{
				enemy->MoveToPlayer(player->GetCollisionShape());
				enemy->Update(elapsedSec);
			}
		}
	}
}

void Level::DrawDebugMode() const
{
	utils::SetColor(Color4f{ 1,1,1,1 });
	for (auto i : m_Vertices)
	{
		utils::DrawPolygon(i, true, 5.f);
	}
	utils::SetColor(Color4f{ 1,0,0,1 });
	for (const GameObject* i : m_pObjects)
	{
		utils::DrawRect(i->GetCollisionShape());
	}
	utils::SetColor(Color4f{ 0,1,0,1 });
	for (const GameObject* i : m_pObjects)
	{
		utils::DrawRect(i->GetShape());
	}
}

void Level::ClearLevel()
{
	for (GameObject* i : m_pObjects)
	{
		delete i;
		m_pObjects.pop_back();
	}
	delete m_pLevelTexture;
	m_Vertices.clear();
}

void Level::ActivatePortal() const
{
	for (GameObject* i : m_pObjects)
	{
		if (typeid(*i) == typeid(Portal))
		{
			Portal* portal{ dynamic_cast<Portal*>(i) };
			portal->ToggleActive();
		}
	}
}
