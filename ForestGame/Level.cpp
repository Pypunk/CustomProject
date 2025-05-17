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
#include <queue>

struct GameObjectComparator {
	bool operator()(const std::shared_ptr<GameObject> lhs, const std::shared_ptr<GameObject> rhs) const {
		return lhs->GetShape().bottom < rhs->GetShape().bottom;
	}
};

Level::Level()
	:m_IsDebugMode{false}
	,m_pLevelTexture{nullptr}
	,m_IsLevelEnded{false}
{
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
	m_pObjects.push_back(std::make_shared<Skeleton>( Point2f{450.f,360.f} ));
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

	m_pObjects.push_back(std::make_shared<Foliage>(position,type));
}

void Level::CreateStone(const std::string& stone)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", stone));

	m_pObjects.push_back(std::make_shared<Stone>( position ));
}

void Level::CreatePortal(const std::string& portal)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", portal));

	m_pObjects.push_back(std::make_shared<Portal>( position ));
}

void Level::CreateBackgroundTexture(const std::string& texture)
{
	std::string path{ "Resources/Textures/Level/" };

	m_pLevelTexture = std::make_unique<Texture>( path + GetAttributeValue("Texture",texture ));
	SVGParser::GetVerticesFromSvgFile(path + GetAttributeValue("SVG", texture), m_Vertices);
}

void Level::CreatePlayer(const std::string& player)
{
	Point2f position = ToPoint2f(GetAttributeValue("Position", player));

	m_pObjects.push_back(std::make_shared<Player>( position ));
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

void Level::Update(float elapsedSec)
{
	UpdateGameObjects(elapsedSec);
	std::priority_queue<std::shared_ptr<GameObject>, std::vector<std::shared_ptr<GameObject>>, GameObjectComparator> objectQueue;
	for (const auto& obj : m_pObjects) {
		objectQueue.push(obj);
	}

	m_pObjects.clear();
	while (!objectQueue.empty()) {
		m_pObjects.push_back(objectQueue.top());
		objectQueue.pop();
	}
}

void Level::UpdatePlayer(std::shared_ptr<Player> player, float elapsedSec)
{
	if (player)
	{
		player->Update(elapsedSec);
		player->DoCollisions(m_Vertices, elapsedSec);
	}
}

void Level::HandlePlayerCollision(std::shared_ptr<Player> player, float elapsedSec)
{
	if (!player)
	{
		return;
	}

	for (const auto& obj : m_pObjects)
	{
		if (obj != player) {
			player->DoCollisions(obj, elapsedSec);
		}
	}
}

void Level::MoveEnemyToPlayer(std::shared_ptr<Enemy> enemy, const Rectf& playerShape, float elapsedSec)
{
	if (enemy)
	{
		enemy->MoveToPlayer(playerShape);
	}
}

void Level::UpdateEnemy(std::shared_ptr<Enemy> enemy, float elapsedSec)
{
	if (enemy) {
		enemy->Update(elapsedSec);
		enemy->DoCollisions(m_Vertices, elapsedSec);
	}
}

void Level::HandleEnemyCollision(std::shared_ptr<Enemy> enemy, float elapsedSec)
{
	if (!enemy)
	{
		return;
	}

	for (const auto& obj : m_pObjects)
	{
		if (obj != enemy) {
			enemy->DoCollisions(obj, elapsedSec);
		}
	}
}

void Level::HandlePortal(std::shared_ptr<Portal> portal, std::shared_ptr<Player> player)
{
	if (portal && player && portal->IsPlayerOverLapping(player))
	{
		m_IsLevelEnded = true;
	}
}

void Level::Draw(std::shared_ptr<Camera> camera) const
{
	glPushMatrix();
	for (const auto&  i: m_pObjects)
	{
		if (std::shared_ptr<Player> player = dynamic_pointer_cast<Player>(i))
		{
			camera->Draw(player->GetShape());
		}
	}
	m_pLevelTexture->Draw(GetLevelShape());
	for (const auto& i : m_pObjects)
	{
		i->Draw();
	}
	if (m_IsDebugMode)
	{
		DrawDebugMode();
	}
	glPopMatrix();
}

void Level::UpdateGameObjects(float elapsedSec)
{
	std::shared_ptr<Player> player = nullptr;

	for (const auto& i : m_pObjects) 
	{
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(i)) 
		{
			UpdatePlayer(player, elapsedSec);
			HandlePlayerCollision(player, elapsedSec);

			for (const auto& j : m_pObjects) 
			{
				if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(j))
				{
					if (std::shared_ptr<Skeleton> skeleton = std::dynamic_pointer_cast<Skeleton>(j))
					{
						std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Skeleton>(j);
						MoveEnemyToPlayer(enemy, player->GetShape(), elapsedSec);
						UpdateEnemy(enemy, elapsedSec);
						HandleEnemyCollision(enemy, elapsedSec);
					}
				}
			}
		}

		if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(i)) 
		{
			HandlePortal(portal, player);
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
	for (const auto& i : m_pObjects)
	{
		utils::DrawRect(i->GetCollisionShape());
	}
	utils::SetColor(Color4f{ 0,1,0,1 });
	for (const auto& i : m_pObjects)
	{
		utils::DrawRect(i->GetShape());
	}
}

void Level::ClearLevel()
{
	m_Vertices.clear();
}

void Level::ActivatePortal() const
{
	for (const auto& i : m_pObjects)
	{
		if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(i))
		{
			portal->ToggleActive();
		}
	}
}
