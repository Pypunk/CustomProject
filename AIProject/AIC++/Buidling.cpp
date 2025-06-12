#include "pch.h"
#include "Buidling.h"
#include "AllUnits.h"
#include <cmath>

Building::Building(const Point2f& position)
	:GameObject(position,100.f,100.f)
	,m_ProgressBar{position.x,position.y-20.f,m_Shape.width,10.f}
	,m_ProgressFill{m_ProgressBar.GetBottomLeft(),0,10.f}
	,m_ProductionAmount{}
	,m_ProductionSpeed{0.f}
	,m_Price{0,0,0}
{
	m_RallyPoint = GetCenter();
}

GameObject::GameObjectType Building::GetType() const
{
	return GameObject::GameObjectType::Building;
}

void Building::Draw() const
{
	switch (GetBuildingType())
	{
	case Building::BuildingType::TownCenter:
		utils::SetColor(Color4f{ 0,0,1,1 });
		break;
	case Building::BuildingType::Barracks:
		utils::SetColor(Color4f{ 1,0,1,1 });
		break;
	case Building::BuildingType::ArcheryRange:
		utils::SetColor(Color4f{ 0,1,1,1 });
		break;
	case Building::BuildingType::Stables:
		utils::SetColor(Color4f{ 1,1,0,1 });
		break;
	default:
		break;
	}
	GameObject::Draw();
}

void Building::DrawExtra() const
{
	utils::DrawRect(m_ProgressBar);
	utils::SetColor(Color4f{ 0.f,1.f,0.f,0.5f });
	utils::FillRect(m_ProgressFill);
	if (IsSelected())
	{
		utils::DrawArrow(GetCenter(), m_RallyPoint, 10.f); // Or DrawLine()
	}
}

void Building::Update(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec)
{
	if (m_ProductionAmount > 0)
	{
		AddProgress(m_ProductionSpeed * elapsedSec);
	}
}

void Building::AddProgress(float progress)
{
	m_ProgressFill.width = fmod(m_ProgressFill.width + progress, m_ProgressBar.width+1.f);
}

std::unique_ptr<Unit> Building::CreateUnit(Point2f position, BuildingType type)
{
	// Define spawn radius or box around building
	const float radius = 50.f;

	// Center of building
	Point2f center = GetCenter(); // Assuming this is in GameObject

	// Generate a random offset within radius
	float angle = utils::GetRand(0.f, 2.f * float(M_PI));
	float dist = utils::GetRand(20.f, radius); // start slightly away from the center

	float offsetX = std::cos(angle) * dist;
	float offsetY = std::sin(angle) * dist;

	Point2f spawnPos{ center.x + offsetX, center.y + offsetY };
	std::unique_ptr<Unit> unit;

	switch (type)
	{
	case Building::BuildingType::TownCenter:
		unit = std::make_unique<Villager>(position);
		break;
	case Building::BuildingType::Barracks:
		unit = std::make_unique<Infantry>(position);
		break;
	case Building::BuildingType::ArcheryRange:
		unit = std::make_unique<Ranged>(position);
		break;
	case Building::BuildingType::Stables:
		unit = std::make_unique<Cavalry>(position);
		break;
	default:
		break;
	}
	unit->CommandAI(m_RallyPoint);
	m_ProductionAmount--;
	return unit;
}

void Building::SetRallyPoint(const Point2f& point)
{
	m_RallyPoint = point;
}

void Building::SetCenter(const Point2f& center)
{
	m_Shape.SetBottomLeft(Point2f{ center.x - m_Shape.width / 2, center.y - m_Shape.height / 2 });
	SetRallyPoint(center);
	m_ProgressBar.SetBottomLeft(m_Shape.GetBottomLeft(0.f, -20.f));
	m_ProgressFill.SetBottomLeft(m_ProgressBar.GetBottomLeft());
	m_MaxHealth.SetBottomLeft(m_Shape.GetTopLeft(0.f, 10.f));
	m_CurrentHealth.SetBottomLeft(m_MaxHealth.GetBottomLeft());
}

bool Building::IsProductionFinished() const
{
	return m_ProgressFill.width >= m_ProgressBar.width;
}

void Building::ResetProduction()
{
	m_ProgressFill.width = 0.f;
}

void Building::StartProduction(int amount)
{
	m_ProductionAmount = amount;
}

Point2f Building::GetRallyPoint()
{
	return m_RallyPoint;
}
