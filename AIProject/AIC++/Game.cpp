#include "pch.h"
#include "Game.h"
#include "Unit.h"
#include "PatrolPoints.h"
#include "SelectionRect.h"
#include <iostream>
#include "Buidling.h"
Game::Game(const Window& window)
	:m_Window{ window }
	, selectionRect{ new SelectionRect{Rectf{0,0,window.width,window.height}} }
	, m_IsRightMousePressed{ false }
	, m_RightCurrentPos{ m_MousePos }
{
	Initialize();
	float size{ 50.f };
	Point2f Position{ window.width / 2.f - (m_AmountOfObjects * size / 2.f),window.height / 2.f };
	for (int i{}; i < m_AmountOfObjects; i++)
	{
		m_pObjects.push_back(new Unit{ Point2f{Position.x,Position.y} });
		Position.x += size;
	}
	Position.x += size;
	m_pObjects.push_back(new Building{ Point2f{ Position.x,Position.y } });
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
	for (size_t i{}; i < m_pObjects.size(); ++i) 
	{
		delete m_pObjects[i];
	}
	delete selectionRect;
}

void Game::Update( float elapsedSec )
{
	for (GameObject* object : m_pObjects)
	{
		object->Update(m_pObjects, elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (const GameObject* object : m_pObjects)
	{
		object->Draw();
	}
	utils::DrawPoint(m_MousePos, 5.f);
	if (m_IsRightMousePressed && selectedUnits.size() >= 1)
	{
		utils::SetColor(Color4f{ 1,1,0,1 });
		utils::DrawArrow(m_RightMouseStartPos, m_RightCurrentPos, 10);
	}
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
	case SDLK_f:	
		for (GameObject* object : m_pObjects) 
		{
			Unit* unit = dynamic_cast<Unit*>(object);
			if (unit != nullptr)
			{
				unit->ToggleState(Unit::State::Following);
			}
		}
		break;
	case SDLK_l:
		for (GameObject* object : m_pObjects)
		{
			Unit* unit = dynamic_cast<Unit*>(object);
			if (unit != nullptr)
			{
				unit->ToggleState(Unit::State::Face);
			}
		}
		break;
	case SDLK_p:
		for (GameObject* object : m_pObjects)
		{
			Unit* unit = dynamic_cast<Unit*>(object);
			if (unit != nullptr)
			{
				unit->ToggleState(Unit::State::Patrolling);
			}
		}
		break;
	}
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
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		for (size_t i{}; i < m_pObjects.size(); ++i)
		{
			m_pObjects[i]->SetSelected(m_MousePos, selectionRect->GetRect());
		}
		selectionRect->RemoveRect();
		selectedUnits.clear();
		for (GameObject* object : m_pObjects)
		{
			Unit* unit = dynamic_cast<Unit*>(object);
			if (unit != nullptr && unit->IsSelected())
			{
				selectedUnits.push_back(unit);
			}
			Building* building = dynamic_cast<Building*>(object);
			if (building != nullptr && building->IsSelected())
			{
				selectedBuildings.push_back(building);
			}
		}
		break;
	case SDL_BUTTON_RIGHT:
		if (m_IsRightMousePressed)
		{
			m_IsRightMousePressed = false;
			m_RightMouseEndPos = m_MousePos;

			IssueDirectionalCommand(m_RightMouseStartPos, m_RightMouseEndPos);
			m_RightCurrentPos = m_MousePos;
		}
		std::cout << "<--Printing Selection Results-->\n\n";
		std::cout << selectedUnits.size() << " untis selected\n";
		std::cout << selectedBuildings.size() << " buildings Selected\n";
		std::cout << "\n";
		break;
	case SDL_BUTTON_MIDDLE:
		for (GameObject* object : m_pObjects)
		{
			Unit* unit = dynamic_cast<Unit*>(object);
			if (unit != nullptr)
			{
				unit->RemovePatrolPoints(m_MousePos);
			}
		}
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

	for (size_t i = 0; i < selectedUnits.size(); ++i)
	{
		selectedUnits[i]->SetFormationOffset(offsets[i]);
		selectedUnits[i]->SetFacingTargetOffset(facing * 100.f);
		selectedUnits[i]->CommandAI(start); // Shared origin
	}
}
