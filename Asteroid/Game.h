#pragma once
using namespace utils;
class Spaceship;
class Asteroid;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Asteroid - SnauwaertPieter" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const float g_HorSpeed{ 10.f };
const float g_VertSpeed{ 10.f };
int g_AsteroidAmount{ 5 };
const float g_AsteroidSize{ 15.f };
float g_SpawnTimer{ 0 };
bool g_isPressed{ false };
Spaceship* g_pSpaceship{ nullptr };
std::vector<Asteroid*>g_pAsteroids;
Texture g_GameOverText;
Texture g_RToRestartText;
Texture g_AmountOfAsteroidText;
Texture g_Background;
// Declare your own functions here
void CreateSpaceship();
void CreateAsteroids();
void UpdateSpaceship(float elapsedSec);
void UpdateSpaceshipVelocityX(float step);
void UpdateSpaceshipVelocityY(float step);
void UpdateAsteroids(float elapsedSec);
void UpdateAsteroidCollisions(float elapsedSec);
void SetNewAsteroidX(float randHeight, const int index);
void SetNewAsteroidY(float randWidth, const int index);
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
