#include "pch.h"
#include "Game.h"
#include "Character.h"
#include "utils.h"
#include "Tile.h"
using namespace utils;
Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_pCharacter{new Character{Point2f{m_Window.width/2.f, m_Window.height/2.f}}}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	Point2f temp{};
	for (int i{}; i < m_AmountOfTiles; ++i)
	{
		m_pTiles.push_back(new Tile{ temp });
		temp.x += m_pTiles[i]->GetShape().width;
		if (i != 0)
			m_pTiles[i]->DetectPreviousTile(m_pTiles[i - 1]);
	}
}

void Game::Cleanup( )
{
	delete m_pCharacter;
	m_pCharacter = nullptr;
	for (Tile* i : m_pTiles)
	{
		delete i;
		i = nullptr;
	}
	m_pTiles.clear();
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	m_pCharacter->Update(elapsedSec);
	for (Tile* i : m_pTiles)
	{
		m_pCharacter->DoPlatformCollision(i);
		i->Update(elapsedSec, float(m_AmountOfTiles));
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (Tile* i : m_pTiles)
	{
		i->Draw();
	}
	m_pCharacter->Draw();
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
	case SDLK_SPACE:
		m_pCharacter->Jump();
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
