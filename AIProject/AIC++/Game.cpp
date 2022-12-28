#include "pch.h"
#include "Game.h"
#include "AI.h"
#include "PatrolPoints.h"
Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_pAI{ new AI{Point2f{window.width / 2.f,window.height / 2.f}} }
	,m_Target{}
	, m_pPatrolPoints{ new PatrolPoints{} }
{
	Initialize( );
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
	delete m_pAI;
	delete m_pPatrolPoints;
}

void Game::Update( float elapsedSec )
{
	if (m_Target.x != 0 && m_Target.y != 0)
	{
		//m_pAI->Face(m_Target, elapsedSec);
		//m_pAI->Follow(m_Target, elapsedSec);
		//m_pAI->Evade(m_Target, elapsedSec);
		m_pAI->Patrol(*m_pPatrolPoints, elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_pAI->Draw();
	utils::DrawPoint(m_Target, 5.f);
	m_pPatrolPoints->DrawDebug();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
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
	m_MousePos = Point2f{ float(e.x),float(e.y) };
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
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_Target = m_MousePos;
		m_pPatrolPoints->AddPoint(m_MousePos);
		break;
	case SDL_BUTTON_RIGHT:
		m_pPatrolPoints->RemovePoint(m_MousePos);
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
