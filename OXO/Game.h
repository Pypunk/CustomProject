#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Tic Tac Toe" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const int cols{4};
const int rows{cols};
Rectf g_Rect[cols][rows]{};
enum class RectState
{
	unclicked,
	o,
	x,
	won
};
RectState g_State[cols][rows];
bool Player1{ true };
bool g_IsGameDone{ false };
Point2f g_MousePos{};

#pragma region gridFunctions
void CreateGrid();
void DrawGrid();
void ResetGrid();
void UpdateGrid();
void CreateO(float radius, const Rectf& rect);
void CreateX(float lenght, const Rectf& rect);
#pragma endregion gridFunctions

#pragma region winFunctions
void CheckWinStates();
bool checkColumnsForO(RectState states[cols][rows]);
bool checkRowsForO(RectState states[cols][rows]);
bool checkDiagonalForO(RectState states[cols][rows]);
bool checkForWinO(RectState states[cols][rows]);


bool checkColumnsForX(RectState states[cols][rows]);
bool checkRowsForX(RectState states[cols][rows]);
bool checkDiagonalForX(RectState states[cols][rows]);
bool checkForWinX(RectState states[cols][rows]);
#pragma endregion winFunctions

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
