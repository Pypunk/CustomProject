#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,noRect{ window.width - 200.f,60,150,50 }
	,yesRect{50,60,150,50}
	, m_pNoText{ new Texture{"No","Fonts/Roboto-Regular.ttf",50,Color4f{0,0,0,1}} }
	, m_pYesText{ new Texture{"Yes","Fonts/Roboto-Regular.ttf",50,Color4f{0,0,0,1}} }
	, m_pNextTest{ new Texture{"Next","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1}} }
	, m_pQnA{ new Texture{"Do you love me?","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1}} }
	, m_pEndTexture{new Texture{"Textures/End.png"}}
	,m_pHeart{new Texture{"Textures/heart.png"}}
	, nextRect{window.width/2.f-75.f,window.height/2.f-25.f,150.f,50.f}
	,isEnd{false}
	,showNext{false}
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
	delete m_pNoText;
	delete m_pYesText;
	delete m_pQnA;
	delete m_pEndTexture;
	delete m_pNextTest;
	delete m_pHeart;
}

void Game::Update( float elapsedSec )
{
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
	if (clickCounter == 1 && isYes)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "Are you sure?","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1} };
	}
	if (clickCounter == 2 && isYes)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "Okay","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1} };
		timer += elapsedSec;
		if (1 <= timer)
		{
			showNext = true;
			delete m_pEndTexture;
			m_pEndTexture = new Texture{ "Textures/end.png" };
			clickCounter = 0;
			isEnd = true;
		}
	}
	if (clickCounter == 1 && isNo)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "But... Are you sure?","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1} };
	}
	if (clickCounter == 2 && isNo)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "Okay","Fonts/Roboto-Regular.ttf",50,Color4f{1,1,1,1} };
		timer += elapsedSec;
		if (1 <= timer)
		{
			showNext = true;
			delete m_pEndTexture;
			m_pEndTexture = new Texture{ "Textures/jump.jpg" };
			clickCounter = 0;
			isEnd = true;
		}
	}
	if (showNext && clickCounter == 1)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "Whatever you answered, it doesnt matter haha","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 2)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "I love you very much and nothing can change that","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 3)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "I want to stay with you for the rest of my life!","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 4)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "You're the best thing that has ever happened to me","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 5)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "You're so beautilful and pretty and sexy...","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 6)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "You're also very kind and funny and weird like me","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 7)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "I cant wait until we meet eachother","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 8)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "But until then, this will have to do","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
	if (showNext && clickCounter == 9)
	{
		delete m_pQnA;
		m_pQnA = new Texture{ "Happy birthday! I love you sooo much!","Fonts/Roboto-Regular.ttf",25,Color4f{1,1,1,1} };
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	if (showNext)
	{
		utils::SetColor(Color4f{ 1,1,1,1 });
		m_pHeart->Draw(Rectf{ 0,0,m_Window.width,m_Window.height });
		utils::DrawRect(nextRect);
		m_pNextTest->Draw(nextRect.GetBottomCenter(-m_pNextTest->GetWidth() / 2.f));
		if (clickCounter > 0)
		{
			m_pQnA->Draw(Point2f{ m_Window.width / 2.f - m_pQnA->GetWidth() / 2.f,m_Window.height / 2.f - m_pQnA->GetHeight() / 2.f });
		}
	}
	if (clickCounter < 2 && !showNext)
	{
		utils::SetColor(Color4f{ 1,1,1,1 });
		utils::FillRect(noRect);
		utils::FillRect(yesRect);
		utils::SetColor(Color4f{ 0,0,0,1 });
		utils::DrawRect(noRect, 3.f);
		utils::DrawRect(yesRect, 3.f);
		m_pNoText->Draw(noRect.GetBottomCenter(-m_pNoText->GetWidth() / 2.f));
		m_pYesText->Draw(yesRect.GetBottomCenter(-m_pYesText->GetWidth() / 2.f));
	}
	if (!isEnd)
	{
		m_pQnA->Draw(Point2f{ m_Window.width / 2.f - m_pQnA->GetWidth() / 2.f,m_Window.height / 2.f - m_pQnA->GetHeight() / 2.f });
	}
	else
	{
		m_pEndTexture->Draw(Rectf{ 0,0,m_Window.width,m_Window.height });
		utils::DrawRect(nextRect);
		m_pNextTest->Draw(nextRect.GetBottomCenter(-m_pNextTest->GetWidth() / 2.f));
	}
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
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	Point2f mouse{ float(e.x),float(e.y) };
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		if (utils::IsPointInRect(mouse, noRect) && !showNext)
		{
			clickCounter++;
			isNo = true;
			isYes = false;
		}
		if (utils::IsPointInRect(mouse, yesRect) && !showNext)
		{
			clickCounter++;
			if (isNo)
			{
				isYes = false;
			}
			else
			{
				isYes = true;
				isNo = false;
			}

		}
		if (utils::IsPointInRect(mouse, nextRect) && showNext)
		{
			clickCounter++;
			isEnd = false;
			isYes = false;
			isNo = false;
			if (clickCounter == 1)
			{
				nextRect.bottom -= nextRect.height * 4.f;
			}
		}
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
