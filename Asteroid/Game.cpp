#include "pch.h"
#include "Game.h"
#include <iostream>
#include "Spaceship.h"
#include "asteroid.h"
#include <vector>
//Basic game functions
#pragma region gameFunctions											
void Start()
{
	CreateSpaceship();
	CreateAsteroids();
	TextureFromString("Game Over!", "Resources/DIN-Light.otf", 80, Color4f{1,1,1,1}, g_GameOverText);
	TextureFromString("Press R to restart!", "Resources/DIN-Light.otf", 40, Color4f{ 1,1,1,1 }, g_RToRestartText);
	std::string asteroidsAmountString{ "Amount of asteroids: " };
	asteroidsAmountString += std::to_string(g_AsteroidAmount);
	TextureFromString(asteroidsAmountString, "Resources/DIN-Light.otf", 20, Color4f{ 1,1,1,1 }, g_AmountOfAsteroidText);
	TextureFromFile("Resources/Background.jpg", g_Background);
}

void Draw()
{
	const Color4f backgroundColor{ 0,0,0,1 };
	ClearBackground(backgroundColor.r, backgroundColor.g, backgroundColor.b);
	DrawTexture(g_Background, Point2f{ 0,0 });
	g_pSpaceship->Draw(g_WindowWidth,g_WindowHeight);
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		g_pAsteroids[i]->Draw();
	}
	const Point2f asteroidAmountTextPos{ 0,g_WindowHeight - g_AmountOfAsteroidText.height };
	DrawTexture(g_AmountOfAsteroidText, asteroidAmountTextPos);
	if (g_pSpaceship->IsDead())
	{
		const Point2f gameOverTextPos{ g_WindowWidth / 2 - g_GameOverText.width / 2,g_WindowHeight / 2 - g_GameOverText.height / 2+g_RToRestartText.height};
		DrawTexture(g_GameOverText, gameOverTextPos);
		const Point2f rToRestartTextPos{ g_WindowWidth / 2 - g_RToRestartText.width / 2,g_WindowHeight / 2 - g_RToRestartText.height / 2-g_RToRestartText.height};
		DrawTexture(g_RToRestartText, rToRestartTextPos);
	}
}

void Update(float elapsedSec)
{
	if (!g_pSpaceship->IsDead())
	{
		UpdateSpaceship(elapsedSec);
		UpdateAsteroids(elapsedSec);

		// e.g. Check keyboard state
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			g_pSpaceship->SetHorVelocity(g_HorSpeed);
			g_isPressed = true;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			g_pSpaceship->SetHorVelocity(-g_HorSpeed);
			g_isPressed = true;
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			g_pSpaceship->SetVertVelocity(-g_VertSpeed);
			g_isPressed = true;
		}
		if (pStates[SDL_SCANCODE_UP])
		{
			g_pSpaceship->SetVertVelocity(g_VertSpeed);
			g_isPressed = true;
		}
		g_SpawnTimer += elapsedSec;
		Point2f asteroidPosition{};
		if (10 < g_SpawnTimer)
		{
			g_SpawnTimer = 0;
			asteroidPosition.x = float(rand() % int(g_WindowWidth));
			asteroidPosition.y = float(rand() % int(g_WindowHeight));
			g_pAsteroids.push_back(new Asteroid{ asteroidPosition,g_pSpaceship });
			g_AsteroidAmount++;
			DeleteTexture(g_AmountOfAsteroidText);
			std::string asteroidsAmountString{ "Amount of asteroids: " };
			asteroidsAmountString += std::to_string(g_AsteroidAmount);
			TextureFromString(asteroidsAmountString, "Resources/DIN-Light.otf", 20, Color4f{ 1,1,1,1 }, g_AmountOfAsteroidText);
		}
	}
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
	g_pAsteroids.clear();
	DeleteTexture(g_GameOverText);
	DeleteTexture(g_RToRestartText);
	DeleteTexture(g_AmountOfAsteroidText);
	DeleteTexture(g_Background);
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
	case SDLK_r:
		if (g_pSpaceship->IsDead())
		{
			delete g_pSpaceship;
			g_pSpaceship = nullptr;
			for (int i{}; i < g_AsteroidAmount; ++i)
			{
				delete g_pAsteroids[i];
				g_pAsteroids[i] = nullptr;
			}
			g_pAsteroids.clear();
			g_AsteroidAmount = 5;
			CreateSpaceship();
			CreateAsteroids();
			g_SpawnTimer = 0;
			DeleteTexture(g_AmountOfAsteroidText);
			std::string asteroidsAmountString{ "Amount of asteroids: " };
			asteroidsAmountString += std::to_string(g_AsteroidAmount);
			TextureFromString(asteroidsAmountString, "Resources/DIN-Light.otf", 20, Color4f{ 1,1,1,1 }, g_AmountOfAsteroidText);
		}
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
	float starshipSize{ 15.f };
	g_pSpaceship = new Spaceship{ starshipPosition,starshipSize };
}
void CreateAsteroids()
{
	Point2f asteroidPosition{};
	for (int i{}; i < g_AsteroidAmount; ++i)
	{
		asteroidPosition.x = float(rand() % int(g_WindowWidth));
		asteroidPosition.y = float(rand() % int(g_WindowHeight));
		g_pAsteroids.push_back(new Asteroid{ asteroidPosition,g_pSpaceship });
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
	bool invincible{ g_pSpaceship->GetInvincible() };
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
		if ((g_pSpaceship->IsHit(g_pAsteroids[i]->GetShape()) && !g_pSpaceship->GetInvincible()) 
			|| (g_pSpaceship->IsRocketHit(g_pAsteroids[i]->GetShape()) && !g_pSpaceship->GetInvincible()))
		{
			g_pSpaceship->SetZeroVelocity();
			delete g_pAsteroids[i];
			g_pAsteroids[i] = nullptr;
			g_pAsteroids[i] = new Asteroid{ Point2f{randWidth,randHeight},g_pSpaceship };
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
			g_pAsteroids[index] = new Asteroid{ Point2f{0,randHeight},g_pSpaceship };
		}
	}
	else if (g_pAsteroids[index]->GetVelocity().x < 0)
	{
		if (g_pAsteroids[index]->GetShape().center.x < 0)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{0,randHeight},g_pSpaceship };
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
			g_pAsteroids[index] = new Asteroid{ Point2f{randWidth,0},g_pSpaceship };
		}
	}
	else if (g_pAsteroids[index]->GetVelocity().y < 0)
	{
		if (g_pAsteroids[index]->GetShape().center.y < 0)
		{
			delete g_pAsteroids[index];
			g_pAsteroids[index] = nullptr;
			g_pAsteroids[index] = new Asteroid{ Point2f{randWidth,0},g_pSpaceship };
		}
	}
}
#pragma endregion ownDefinitions