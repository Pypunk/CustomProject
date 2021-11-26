#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitializeObstacles();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	for (int i{}; i < 3; ++i)
	{
		FillRect(g_Obstacles[i]);
	}
	SetColor(g_Color);
	FillRect(g_Character);
	SetColor(1, 1, 1, 1);
	DrawHealth();
}

void Update(float elapsedSec)
{
	// process input, do physics 
	UpdateCharacter(elapsedSec);
	UpdateObstacles(elapsedSec);
	if (isHit)
	{
		g_HealthAmount--;
		isHit = false;
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
		g_CurrentState = jumpState::jumping;
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
void UpdateCharacter(float elapsedSec)
{
	g_Velocity.y += g_Gravity;
	g_Character.bottom += Scale(g_Velocity, elapsedSec).y;
	if (g_Character.bottom <= 0.f)
	{
		g_Velocity.y = SetNullvector().y;
		g_Character.bottom = 0.f;
	}
	std::cout << ToString(g_Velocity) << std::endl;
	if (g_Velocity.y < -980.f)
	{
		g_CurrentState = jumpState::onground;
	}
	CheckJumpState(elapsedSec);
}
void CheckJumpState(float elapsedSec)
{
	switch (g_CurrentState)
	{
	case jumpState::jumping:
		g_Character.bottom += g_JumpVelocity * elapsedSec;
		break;
	}
}
void DrawHealth()
{
	const float radius{ 10 };
	for (int i{}; i < g_HealthAmount; ++i)
	{
		const Point2f center{ (g_WindowWidth - radius * 2) - (radius * 2) * i,g_WindowHeight - radius * 2 };
		DrawCircle(center, radius);
	}
}
void InitializeObstacles()
{
	const float size{ 50 };
	g_Character = Rectf{ g_WindowWidth / 2 - size / 2,g_WindowHeight / 2 - size / 2,size,size };
	for (int i{}; i < 3; ++i)
	{
		switch (i)
		{
		case 0:
			g_Obstacles[i] = Rectf{ g_WindowWidth - size / 2,0,size / 2,size / 2 };
			break;
		case 1:
			g_Obstacles[i] = Rectf{ g_WindowWidth + size * 3,0,size / 2,size / 2 };
			break;
		case 2:
			g_Obstacles[i] = Rectf{ g_WindowWidth + size * 6,0,size / 2,size / 2 };
			break;
		};
	}
	g_Speed = 150.f;
}
void UpdateObstacles(float elapsedSec)
{
	for (int i{}; i < 3; ++i)
	{
		g_Obstacles[i].left -= g_Speed * elapsedSec;
		if (g_Obstacles[i].left <= 0)
		{
			g_Obstacles[i].left = g_WindowWidth;
		}
		if (IsOverlapping(g_Character, g_Obstacles[i]))
		{
			const float size{ 50 };
			isHit = true;
			switch (i)
			{
			case 0:
				g_Obstacles[i].left += g_WindowWidth - size / 2;
				break;
			case 1:
				g_Obstacles[i].left += g_WindowWidth - size / 2;
				break;
			case 2:
				g_Obstacles[i].left += g_WindowWidth - size / 2;
				break;
			};
		}
	}
}
#pragma endregion ownDefinitions