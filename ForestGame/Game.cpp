#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Level.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_pCamera{ new Camera{window.width,window.height} }
	, m_pLevel{ new Level{} }
	, m_IsLevelLoading{false}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pLevel->CreateLevelFromFile("Resources/LevelData/testLevel.xml");
	m_pCamera->SetLevelBoundaries(m_pLevel->GetLevelShape());
}

void Game::Cleanup( )
{
	delete m_pCamera;
	delete m_pLevel;
}

void Game::Update( float elapsedSec )
{
	m_pLevel->Update(elapsedSec);
	if (m_pLevel->IsLevelEnded())
	{
		m_IsLevelLoading = true;
	}
	if (m_IsLevelLoading)
	{
		m_pLevel->CreateLevelFromFile("Resources/LevelData/level_1.xml");
		m_pCamera->SetLevelBoundaries(m_pLevel->GetLevelShape());
		m_IsLevelLoading = false;
	}
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	m_pLevel->Draw(m_pCamera);
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_RCTRL:
		m_pLevel->ToggleDebugMode();
		break;
	case SDLK_q:
		m_pLevel->ActivatePortal();
		break;
	case SDLK_ESCAPE:
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
