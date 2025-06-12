#include "pch.h"
#include "Game.h"
#include "PatrolPoints.h"
#include "SelectionRect.h"
#include "AllBuildings.h"
#include "AllUnits.h"
#include <iostream>
Game::Game(const Window& window)
	:m_Window{ window }
	, selectionRect{ new SelectionRect{Rectf{0,0,window.width,window.height}} }
	, m_IsRightMousePressed{ false }
	, m_RightCurrentPos{ m_MousePos }
	, m_Resources{ 500,500,500 }
{
	Initialize();
	float size{ 50.f };
	Point2f Position{ window.width / 2.f - (m_AmountOfObjects * size / 2.f),window.height / 2.f };
	for (int i{}; i < m_AmountOfObjects; i++)
	{
		m_pObjects.push_back(std::make_unique<Villager>(Point2f{ Position.x,Position.y }));
		Position.x += size;
	}
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
}

void Game::Cleanup( )
{
	delete selectionRect;
}

void Game::Update( float elapsedSec )
{
	for (const std::unique_ptr<GameObject>& object : m_pObjects)
	{
		if (object)
		{
			object->Update(m_pObjects, elapsedSec);
		}
		Villager* villager = dynamic_cast<Villager*>(object.get());
		if (villager && villager->IsSelected() && villager->IsInBuildMode())
		{
			villager->UpdateBuildingLocation(m_MousePos, m_pObjects);
		}
	}
	std::vector<std::unique_ptr<GameObject>> toSpawn;
	SpawnUnit(toSpawn);
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (const std::unique_ptr<GameObject>& object : m_pObjects)
	{
		if (object)
		{
			object->Draw();
		}
	}
	utils::DrawPoint(m_MousePos, 5.f);
	selectionRect->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_t:
		TurnOnBuildModeForSelectedVillagers();
		m_Resources.Print();
		for (auto& obj : m_pObjects)
		{
			Villager* villager = dynamic_cast<Villager*>(obj.get());
			if (villager && villager->IsInBuildMode())
			{
				villager->SetPlannedBuilding(Building::BuildingType::TownCenter);
			}
		}
		break;
	case SDLK_b:
		TurnOnBuildModeForSelectedVillagers();
		m_Resources.Print();
		for (auto& obj : m_pObjects)
		{
			Villager* villager = dynamic_cast<Villager*>(obj.get());
			if (villager && villager->IsInBuildMode())
			{
				villager->SetPlannedBuilding(Building::BuildingType::Barracks);
			}
		}
		break;
	case SDLK_a:
		TurnOnBuildModeForSelectedVillagers();
		m_Resources.Print();
		for (auto& obj : m_pObjects)
		{
			Villager* villager = dynamic_cast<Villager*>(obj.get());
			if (villager && villager->IsInBuildMode())
			{
				villager->SetPlannedBuilding(Building::BuildingType::ArcheryRange);
			}
		}
		break;
	case SDLK_s:
		TurnOnBuildModeForSelectedVillagers();
		m_Resources.Print();
		for (auto& obj : m_pObjects)
		{
			Villager* villager = dynamic_cast<Villager*>(obj.get());
			if (villager && villager->IsInBuildMode())
			{
				villager->SetPlannedBuilding(Building::BuildingType::Stables);
			}
		}
		break;
	case SDLK_ESCAPE:
		ExitBuildModeForAllVillagers();
		break;
	}
	ManageProduction(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos = Point2f{ float(e.x),float(e.y) };
	selectionRect->CreateRect(m_MousePos);
	if (m_IsRightMousePressed)
	{
		m_RightCurrentPos = m_MousePos;
	}
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		selectionRect->CreateStartPos(m_MousePos);
		break;
	case SDL_BUTTON_RIGHT:
		m_IsRightMousePressed = true;
		m_RightMouseStartPos = m_MousePos;
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	std::vector<std::unique_ptr<GameObject>> toSpawn;
	bool buildingPlaced{ false };

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		ProcessLeftClick(toSpawn, buildingPlaced);
		break;

	case SDL_BUTTON_RIGHT:
		ProcessRightClick();
		break;

	case SDL_BUTTON_MIDDLE:
		ProcessMiddleClick();
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

std::vector<Point2f> Game::GenerateRotatedFormationOffsets(int unitCount, float spacing, const Vector2f& facing)
{
	std::vector<Point2f> offsets;
	const int columns = 3;
	int rows = (unitCount + columns - 1) / columns;

	// Rotation angle
	float angle = std::atan2(facing.y, facing.x);
	float cosA = std::cos(angle);
	float sinA = std::sin(angle);

	for (int i = 0; i < unitCount; ++i)
	{
		int row = i / columns;
		int col = i % columns;

		float x = (col - (columns / 2)) * spacing;
		float y = -(row * spacing); // Backward from front line

		// Rotate the offset
		float rotatedX = x * cosA - y * sinA;
		float rotatedY = x * sinA + y * cosA;

		offsets.emplace_back(Point2f{ rotatedX, rotatedY });
	}
	return offsets;
}

void Game::IssueDirectionalCommand(const Point2f& start, const Point2f& end)
{
	Vector2f facing{ start, end };
	facing = facing.Normalized();

	auto offsets = GenerateRotatedFormationOffsets(static_cast<int>(selectedUnits.size()), 60.f, facing);

	for (Unit* unit : selectedUnits)
	{
		Villager* villager = dynamic_cast<Villager*>(unit);
		unit->CommandAI(start); // Shared origin
	}
}

void Game::ProcessLeftClick(std::vector<std::unique_ptr<GameObject>>& toSpawn, bool& buildingPlaced)
{
	PlaceBuildingIfPossible(toSpawn, buildingPlaced);
	if (buildingPlaced) ExitBuildModeForAllVillagers();

	SelectObjects();
	UpdateSelectionLists();

	for (auto& obj : toSpawn)
	{
		m_pObjects.push_back(std::move(obj));
	}
}

void Game::ProcessRightClick()
{
	if (m_IsRightMousePressed)
	{
		m_IsRightMousePressed = false;
		m_RightMouseEndPos = m_MousePos;
		IssueDirectionalCommand(m_RightMouseStartPos, m_RightMouseEndPos);
		m_RightCurrentPos = m_MousePos;
	}

	for (auto& object : m_pObjects)
	{
		if (Building* building = dynamic_cast<Building*>(object.get()); building && building->IsSelected())
		{
			building->SetRallyPoint(m_MousePos);
		}
	}
	int villagerCounter{};
	int infantryCounter{};
	int rangedCounter{};
	int cavalryCounter{};
	int townCenterCounter{};
	int barracksCounter{};
	int archeryRangeCounter{};
	int stablesCounter{};

	std::cout << "<--Printing Selection Results-->\n\n";
	std::cout << selectedUnits.size() << " units selected\n";
	for (Unit* unit : selectedUnits)
	{
		Villager* villager = dynamic_cast<Villager*>(unit);
		if (villager)
		{
			villagerCounter++;
		}
		Infantry* infantry = dynamic_cast<Infantry*>(unit);
		if (infantry)
		{
			infantryCounter++;
		}
		Ranged* ranged = dynamic_cast<Ranged*>(unit);
		if (ranged)
		{
			rangedCounter++;
		}
		Cavalry* cavalry = dynamic_cast<Cavalry*>(unit);
		if (cavalry)
		{
			cavalryCounter++;
		}
	}
	std::cout << "-- " << villagerCounter << " villagers selected\n";
	std::cout << "-- " << infantryCounter << " infantry selected\n";
	std::cout << "-- " << rangedCounter << " ranged selected\n";
	std::cout << "-- " << cavalryCounter << " cavalry selected\n";
	for (Building* building : selectedBuildings)
	{
		TownCenter* townCenter = dynamic_cast<TownCenter*>(building);
		if (townCenter)
		{
			townCenterCounter++;
		}
		Barracks* barracks = dynamic_cast<Barracks*>(building);
		if (barracks)
		{
			barracksCounter++;
		}
		ArcheryRange* archeryRange = dynamic_cast<ArcheryRange*>(building);
		if (archeryRange)
		{
			archeryRangeCounter++;
		}
		Stables* stables = dynamic_cast<Stables*>(building);
		if (stables)
		{
			stablesCounter++;
		}
	}
	std::cout << selectedBuildings.size() << " buildings selected\n";
	std::cout << "-- " << townCenterCounter << " towncenters selected\n";
	std::cout << "-- " << barracksCounter << " barracks selected\n";
	std::cout << "-- " << archeryRangeCounter << " archery range selected\n";
	std::cout << "-- " << stablesCounter << " stables selected\n\n";
}

void Game::ProcessMiddleClick()
{
	for (const auto& object : m_pObjects)
	{
		if (Unit* unit = dynamic_cast<Unit*>(object.get()))
		{
			unit->RemovePatrolPoints(m_MousePos);
		}
	}
}

void Game::SelectObjects()
{
	bool unitSelected{ false };
	for (auto& obj : m_pObjects)
	{
		Unit* unit = dynamic_cast<Unit*>(obj.get());
		if (unit)
		{
			unit->SetSelected(m_MousePos, selectionRect->GetRect());
			if (unit->IsSelected()) unitSelected = true;
		}
		else
		{
			obj->SetSelected(Point2f{}, Rectf{});
		}
	}
	if (!unitSelected)
	{
		for (const auto& obj : m_pObjects)
		{
			Building* building = dynamic_cast<Building*>(obj.get());
			if (building)
			{
				building->SetSelected(m_MousePos, selectionRect->GetRect());
			}
		}
	}
	selectionRect->RemoveRect();
}

void Game::UpdateSelectionLists()
{
	selectedUnits.clear();
	selectedBuildings.clear();

	for (const auto& object : m_pObjects)
	{
		if (Unit* unit = dynamic_cast<Unit*>(object.get()); unit && unit->IsSelected())
			selectedUnits.insert(unit);

		if (Building* building = dynamic_cast<Building*>(object.get()); building && building->IsSelected())
			selectedBuildings.insert(building);
	}
}

void Game::PlaceBuildingIfPossible(std::vector<std::unique_ptr<GameObject>>& toSpawn, bool& buildingPlaced)
{
	for (const auto& object : m_pObjects)
	{
		Villager* villager = dynamic_cast<Villager*>(object.get());
		if (villager && villager->IsSelected() && villager->IsInBuildMode())
		{
			if (auto building = villager->PlaceBuilding(m_Resources))
			{
				toSpawn.push_back(std::move(building));
			}
			buildingPlaced = true;
			break;
		}
	}
}

void Game::ExitBuildModeForAllVillagers()
{
	for (Unit* unit : selectedUnits)
	{
		Villager* villager = dynamic_cast<Villager*>(unit);
		if (villager && villager->IsInBuildMode())
		{
			villager->ToggleBuildMode(false);
		}
	}
}

void Game::SpawnUnit(std::vector<std::unique_ptr<GameObject>>& toSpawn)
{
	for (const std::unique_ptr<GameObject>& object : m_pObjects)
	{
		if (!object) continue;

		Building* building = dynamic_cast<Building*>(object.get());
		if (building)
		{
			if (building->IsProductionFinished())
			{
				if (auto unit = building->CreateUnit(building->GetCenter(), building->GetBuildingType()))
				{
					toSpawn.push_back(std::move(unit));
				}
				building->ResetProduction();
			}
		}
	}

	for (auto& obj : toSpawn)
	{
		m_pObjects.push_back(std::move(obj));
	}
}

void Game::TurnOnBuildModeForSelectedVillagers()
{
	for (const std::unique_ptr<GameObject>& object : m_pObjects)
	{
		Villager* villager = dynamic_cast<Villager*>(object.get());
		if (villager && villager->IsSelected())
		{
			villager->ToggleBuildMode(true);
		}
	}
}

void Game::ManageProduction(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_KP_PLUS:
		for (auto& obj : m_pObjects)
		{
			Building* building = dynamic_cast<Building*>(obj.get());
			if (building && building->IsSelected())
			{
				building->StartProduction(5);
			}
		}
		break;
	}
}
