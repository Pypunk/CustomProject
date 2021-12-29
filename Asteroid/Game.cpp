#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Spaceship.h"
#include "asteroid.h"
//Basic game functions
#pragma region gameFunctions											
void Start()
{
	CreateSpaceship();
	CreateAsteroids();
}

void Draw()
{
	const Color4f backgroundColor{ 0,0,0,1 };
	ClearBackground(backgroundColor.r, backgroundColor.g, backgroundColor.b);
	g_pSpaceship->Draw();
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		g_pAsteroids[i]->Draw();
	}
}

void Update(float elapsedSec)
{
	UpdateSpaceship(elapsedSec);
	UpdateAsteroids(elapsedSec);

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
	delete g_pSpaceship;
	g_pSpaceship = nullptr;
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		delete g_pAsteroids[i];
		g_pAsteroids[i] = nullptr;
	}
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_UP:
	case SDLK_w:
		g_pSpaceship->SetVertVelocity(g_VertSpeed);
		g_isPressed = true;
		break;
	case SDLK_DOWN:
	case SDLK_s:
		g_pSpaceship->SetVertVelocity(-g_VertSpeed);
		g_isPressed = true;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		g_pSpaceship->SetHorVelocity(-g_HorSpeed);
		g_isPressed = true;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		g_pSpaceship->SetHorVelocity(g_HorSpeed);
		g_isPressed = true;
		break;
	}
}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_UP:
	case SDLK_w:
	case SDLK_DOWN:
	case SDLK_s:
	case SDLK_LEFT:
	case SDLK_a:
	case SDLK_RIGHT:
	case SDLK_d:
		g_isPressed = false;
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
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		g_pSpaceship->SetBulletTarget(mousePos);
		break;
	}
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void CreateSpaceship()
{
	Point2f starshipPosition{ g_WindowWidth / 2.f,g_WindowHeight / 2.f };
	float starshipSize{ 10.f };
	g_pSpaceship = new Spaceship{ starshipPosition,starshipSize };
}
void CreateAsteroids()
{
	Point2f asteroidPosition{};
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		asteroidPosition.x = float(rand() % int(g_WindowWidth));
		asteroidPosition.y = float(rand() % int(g_WindowHeight));
		g_pAsteroids[i] = new Asteroid{ asteroidPosition,g_AsteroidSize,g_pSpaceship };
	}
}
void UpdateSpaceship(float elapsedSec)
{
	g_pSpaceship->Update(elapsedSec, g_WindowWidth, g_WindowHeight);
	if (!g_isPressed)
	{
		const float step{ 5.f };
		UpdateSpaceshipVelocityX(step);
		UpdateSpaceshipVelocityY(step);
	}
}
void UpdateSpaceshipVelocityX(float step)
{
	if (g_pSpaceship->GetCurrentVelocity().x > 0)
	{
		g_pSpaceship->SetHorVelocity(-step);
	}
	else if (g_pSpaceship->GetCurrentVelocity().x < 0)
	{
		g_pSpaceship->SetHorVelocity(step);
	}
}
void UpdateSpaceshipVelocityY(float step)
{
	if (g_pSpaceship->GetCurrentVelocity().y > 0)
	{
		g_pSpaceship->SetVertVelocity(-step);
	}
	else if (g_pSpaceship->GetCurrentVelocity().y < 0)
	{
		g_pSpaceship->SetVertVelocity(step);
	}
}
void UpdateAsteroids(float elapsedSec)
{
	UpdateAsteroidCollisions(elapsedSec);
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		const float randHeight{ float(rand() % int(g_WindowHeight)) };
		SetNewAsteroidX(randHeight, i);
		const float randWidth{ float(rand() % int(g_WindowWidth)) };
		SetNewAsteroidY(randWidth, i);
	}
}
void UpdateAsteroidCollisions(float elapsedSec)
{
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		const float randHeight{ float(rand() % int(g_WindowHeight)) };
		const float randWidth{ float(rand() % int(g_WindowWidth)) };
		g_pAsteroids[i]->Update(elapsedSec);
		if (g_pSpaceship->IsHit(g_pAsteroids[i]->GetShape()) 
			|| g_pSpaceship->IsRocketHit(g_pAsteroids[i]->GetShape()))
		{
			delete g_pAsteroids[i];
			g_pAsteroids[i] = nullptr;
			g_pAsteroids[i] = new Asteroid{ Point2f{randWidth,randHeight},g_AsteroidSize,g_pSpaceship };
		}
	}
}
void SetNewAsteroidX(float randHeight, const int index)
{
	if (g_pAsteroids[index]->GetVelocity().x > 0)
	{
		if (g_pAsteroids[index]->GetShape().center.x > g_WindowWidth)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{0,randHeight},g_AsteroidSize,g_pSpaceship };
		}
	}
	else if (g_pAsteroids[index]->GetVelocity().x < 0)
	{
		if (g_pAsteroids[index]->GetShape().center.x < 0)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{0,randHeight},g_AsteroidSize,g_pSpaceship };
		}
	}
}
void SetNewAsteroidY(float randWidth, const int index)
{
	if (g_pAsteroids[index]->GetVelocity().y > 0)
	{
		if (g_pAsteroids[index]->GetShape().center.y > g_WindowHeight)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{randWidth,0},g_AsteroidSize,g_pSpaceship };
		}
	}
	else if (g_pAsteroids[index]->GetVelocity().y < 0)
	{
		if (g_pAsteroids[index]->GetShape().center.y < 0)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{randWidth,0},g_AsteroidSize,g_pSpaceship };
		}
	}
}
#pragma endregion ownDefinitions