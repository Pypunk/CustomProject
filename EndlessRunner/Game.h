#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Project name - Name, firstname - 1DAExx" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const float g_Gravity{ -9.81f };
float g_Speed{};
float g_HealthAmount{ 5 };
Vector2f g_Velocity{};
Rectf g_Character{};
Rectf g_Obstacles[3]{};
const float g_JumpVelocity{ 500.f };
Color4f g_Color{};
enum class jumpState
{
	jumping,
	onground,
};
bool isHit{ false };
jumpState g_CurrentState{ jumpState::onground };
// Declare your own functions here
void UpdateCharacter(float elapsedSec);
void CheckJumpState(float elapsedSec);
void DrawHealth();
void InitializeObstacles();
void UpdateObstacles(float elapsedSec);
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
