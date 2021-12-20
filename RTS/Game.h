#pragma once
using namespace utils;
class Villager;
class SelectionRect;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Project name - Name, firstname - 1DAExx" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const int g_VillagerAmount{ 10 };
Villager* g_pUnit[g_VillagerAmount]{ nullptr };
Point2f g_MousePos{};
int g_SelectedIndex[g_VillagerAmount];
int g_AmountSelected{};
SelectionRect* g_pSelectionRect;
// Declare your own functions here
void CreateUnits();
void CreateSelectionRect();
void SelectUnits();
void CheckAmountSelected();
void MoveUnits(int amount);
void SetSelectedIndexes(std::vector<int>& indexes);
void SetColsAndRows(int amount, int& cols, int& rows, std::vector<int>& indexes);
void SetMovePositions(int amount, int& cols, int& rows, std::vector<Point2f>& movePositions, std::vector<int>& indexes);
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
