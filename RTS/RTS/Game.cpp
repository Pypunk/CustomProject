#include "pch.h"
#include "Game.h"
#include "SelectionRect.h"
#include <iostream>

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_SelectionRect{}
	, m_pCamera{ new Camera{window.width,window.height} }
	,m_ScreenWidth{window.width}
	,m_ScreenHeight{window.height}
	,m_SingleClickDetected{false}
	,m_DoubleClickDetected{false}
	,m_MouseClick{}
	,m_ClickTimer{}
	,m_Forest{Point2f{100,100},100.f}
{
	Initialize( );
	m_pCamera->SetLevelBoundaries(Rectf{ 0,0,window.width * 2.f,window.height * 2.f });
	m_CameraRect = Rectf{ m_pCamera->GetCameraBottomPos(),window.width,window.height };
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_UnitManager.AddUnit(UnitManager::Type::villager, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::villager, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::villager, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::villager, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::infantry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::infantry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::infantry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::infantry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::cavalry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
	m_UnitManager.AddUnit(UnitManager::Type::cavalry, utils::GetRandPointInRadius(Point2f{ m_Window.width / 2.f,m_Window.height / 2.f }, 50.f));
}

void Game::Cleanup( )
{
	delete m_pCamera;
}

void Game::Update( float elapsedSec )
{
	m_UnitManager.Update(elapsedSec);
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if (utils::IsPointInRect(m_CameraRect.GetTopRight(), m_pCamera->GetLevelBoundaries()))
	{
		if (pStates[SDL_SCANCODE_UP])
		{
			m_CameraRect.bottom += 100.f * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_CameraRect.left += 100.f * elapsedSec;
		}
	}
	else
	{
		m_CameraRect.SetBottomLeft(m_pCamera->GetCameraBottomPos());
	}
	if (utils::IsPointInRect(m_CameraRect.GetBottomLeft(), m_pCamera->GetLevelBoundaries()))
	{
		if (pStates[SDL_SCANCODE_DOWN])
		{
			m_CameraRect.bottom -= 100.f * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_CameraRect.left -= 100.f * elapsedSec;
		}
	}
	else
	{
		m_CameraRect.SetBottomLeft(m_pCamera->GetCameraBottomPos());
	}
	m_SelectionRect.UpdateRect(m_MousePos);
	if (m_SingleClickDetected)
	{
		m_ClickTimer += elapsedSec;
		if (m_MouseClick > 1 && m_ClickTimer < 0.5f)
		{
			m_DoubleClickDetected = true;
		}
		if (m_ClickTimer >= 0.5f)
		{
			m_MouseClick = 0;
			m_ClickTimer = 0.f;
			m_SingleClickDetected = false;
			m_DoubleClickDetected = false;
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	m_pCamera->Draw(m_CameraRect);
	m_UnitManager.Draw();
	m_SelectionRect.Draw();
	utils::DrawRect(m_CameraRect);
	m_Forest.Draw();
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	//switch (e.keysym.sym)
	//{
	//case SDLK_UP:
	//	m_CameraCenterRect.bottom++;
	//	break;
	//case SDLK_DOWN:
	//	m_CameraCenterRect.bottom--;
	//	break;
	//}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos = Point2f{ m_pCamera->GetCameraBottomPos().x + float(e.x), m_pCamera->GetCameraBottomPos().y + float(e.y) };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_SelectionRect.SetFirstPos(m_MousePos);
		m_SingleClickDetected = true;
		m_MouseClick++;
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_UnitManager.SelectUnits(m_MousePos, m_SelectionRect.GetShape());
		m_UnitManager.DoubleClickSelect(m_MousePos, m_DoubleClickDetected, m_CameraRect);
		m_SelectionRect.SetReleased();
		break;
	case SDL_BUTTON_RIGHT:
		m_UnitManager.CheckAmountSelected();
		m_UnitManager.MoveUnits(m_MousePos);
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
