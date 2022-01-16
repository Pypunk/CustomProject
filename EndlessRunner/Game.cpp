#include "pch.h"
#include "Game.h"
#include "Character.h"
#include "Camera.h"
#include "Platform.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	const float size{ 50.f };
	g_pCharacter = new Character{ Point2f{g_WindowWidth / 2.f - size / 2.f,g_WindowHeight},size };
	g_pCamera = new Camera{ g_WindowWidth,g_WindowHeight };
	g_Level = Rectf{ 0,0, g_WindowWidth * 8.f,g_WindowHeight*2.f };
	g_pCamera->SetLevelBoundaries(g_Level);
	Point2f position{ 100.f,50.f };
	float width{ 200.f };
	float height{ 50.f };
	for (int i{}; i < g_AmountOfPlatforms; ++i)
	{
		g_pPlatform[i] = new Platform{ position,width,height };
		position.x += width + GetRand(0.f,100.f);
		width = GetRand(100.f, 300.f);
		position.y = GetRand(0.f, 100.f);
	}
}

void Draw()
{
	ClearBackground();
	// Put your own draw statements here
	glPushMatrix();
	g_pCamera->Transform(g_pCharacter->GetShape());
	g_pCharacter->Draw();
	SetColor(1, 1, 1, 1);
	for (int i{}; i < g_AmountOfPlatforms; ++i)
	{
		g_pPlatform[i]->Draw();
	}
	glPopMatrix();
}

void Update(float elapsedSec)
{
	// process input, do physics 
	g_pCharacter->Update(elapsedSec);
	for (int i{}; i < g_AmountOfPlatforms; ++i)
	{
		g_pCharacter->UpdateCollision(*g_pPlatform[i]);
	}
	// e.g. Check keyboard state
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

void End()
{
	// free game resources here
	delete g_pCharacter;
	g_pCharacter = nullptr;
	delete g_pCamera;
	g_pCamera = nullptr;
	for (int i{}; i < g_AmountOfPlatforms; ++i)
	{
		delete g_pPlatform[i];
		g_pPlatform[i] = nullptr;
	}
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_SPACE:
		g_pCharacter->Jump();
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

#pragma endregion ownDefinitions