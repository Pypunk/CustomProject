#include "pch.h"
#include "Game.h"
#include "Character.h"
#include "Machine.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_pCharacter{new Character{window}}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	const float size{ 100.f };
	const int machineAmount{ 8 };
	int price{};
	Point2f machinePosition{ 75.f,m_Window.height - size };
	for (int i{}; i < machineAmount; ++i)
	{
		m_pMachines.push_back(new Machine{ machinePosition,25.f,10,price });
		machinePosition.x += size;
		price += 5;
	}
}

void Game::Cleanup( )
{
	delete m_pCharacter;
	for (Machine* i : m_pMachines)
	{
		delete i;
	}
}

void Game::Update( float elapsedSec )
{
	for (Machine* i : m_pMachines)
	{
		i->Update(elapsedSec);
		m_pCharacter->Update(elapsedSec, i);
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
	m_pCharacter->Draw();
	for (Machine* i : m_pMachines)
	{
		i->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//switch (e.keysym.sym)
	//{
	//case SDLK_KP_PLUS:
	//	break;
	//case SDLK_KP_MINUS:
	//	break;
	//default:
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	const Point2f mousePos{ float(e.x),float(e.y) };
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (Machine* i : m_pMachines)
		{
			i->SetActive(mousePos, m_pCharacter->GetCurrency());
			i->UpgradeMachine(mousePos, m_pCharacter->GetCurrency());
		}
		break;
	}
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
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
