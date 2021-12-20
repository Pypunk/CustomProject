#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Villager.h"
#include "SelectionRect.h"
//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	CreateUnits();
	CreateSelectionRect();
}

void Draw()
{
	ClearBackground();
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		g_pUnit[i]->Draw();
	}
	g_pSelectionRect->Draw();
	// Put your own draw statements here
}

void Update(float elapsedSec)
{
	// process input, do physics
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		g_pUnit[i]->MoveTo(elapsedSec);
	}
	g_pSelectionRect->UpdateRect(g_MousePos);
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
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		delete g_pUnit[i];
		g_pUnit[i] = nullptr;
	}
	delete g_pSelectionRect;
	g_pSelectionRect = nullptr;
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	g_MousePos = Point2f{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		g_pSelectionRect->SetFirstPos(g_MousePos);
		break;
	}
	}
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		SelectUnits();
		g_pSelectionRect->SetReleased();
		break;
	}
	case SDL_BUTTON_RIGHT:
	{
		CheckAmountSelected();
		MoveUnits(g_AmountSelected);
		break;
	}
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void CreateUnits()
{
	float size{ 20 };
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		Point2f position{ GetRandFloat(size,g_WindowWidth - size),GetRandFloat(size,g_WindowHeight - size) };
		g_pUnit[i] = new Villager{ position,size };
	}
}

void CreateSelectionRect()
{
	g_pSelectionRect = new SelectionRect();
}
void SelectUnits()
{
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		g_pUnit[i]->Deselect();
		g_SelectedIndex[i] = -1;
		if (g_pUnit[i]->SelectUnit(g_MousePos) ||
			g_pUnit[i]->SelectUnit(g_pSelectionRect->GetShape()))
		{
			g_SelectedIndex[i] = i;
		}
	}
}
void CheckAmountSelected()
{
	g_AmountSelected = 0;
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		if (g_SelectedIndex[i] >= 0)
		{
			g_AmountSelected++;
		}
	}
}
void MoveUnits(int amount)
{
	int cols{};
	int rows{};

	std::vector<int> indexesSaved{};
	SetSelectedIndexes(indexesSaved);
	SetColsAndRows(amount, cols, rows, indexesSaved);
	std::vector<Point2f> movePositions{};
	SetMovePositions(amount, cols, rows, movePositions, indexesSaved);
	indexesSaved.clear();
	movePositions.clear();
}
void SetSelectedIndexes(std::vector<int>& indexes)
{
	for (int i{}; i < g_VillagerAmount; ++i)
	{
		if (g_SelectedIndex[i] >= 0)
		{
			indexes.push_back(g_SelectedIndex[i]);
		}
	}
}
void SetColsAndRows(int amount ,int& cols, int& rows, std::vector<int>& indexes)
{
	if (!(amount % 2))
	{
		cols = 2;
		rows = 1;
		if (!(amount % 4))
		{
			cols = 2;
			rows = 2;
			if (!(amount % 8))
			{
				cols = 4;
				rows = 2;
			}
		}
		if (!(amount % 6))
		{
			cols = 3;
			rows = 2;
		}
		if (!(amount % 10))
		{
			cols = 5;
			rows = 2;
			if (!(amount % 20))
			{
				cols = 5;
				rows = 4;
			}
			if (!(amount % 30))
			{
				cols = 5;
				rows = 6;
			}
		}
	}
	else
	{
		cols = amount;
		if (amount == 1)
		{
			rows = 1;
		}
		else
		{
			rows = amount / 2;
		}
	}
	if (g_pUnit[indexes[amount/2]]->GetShape().left < g_MousePos.x - 100.f
		|| g_pUnit[indexes[amount/2]]->GetShape().left > g_MousePos.x + 100.f)
	{
		int temp{ rows };
		rows = cols;
		cols = temp;
	}
}
void SetMovePositions(int amount, int& cols, int& rows, std::vector<Point2f>& movePositions, std::vector<int>& indexes)
{
	Point2f currentPos{ g_MousePos.x - 15.f * cols + 15.f,g_MousePos.y - 15.f };
	for (int i{}; i < rows; ++i)
	{
		for (int j{}; j < cols; ++j)
		{
			movePositions.push_back(currentPos);
			currentPos.x += 30.f;
		}
		currentPos.x = g_MousePos.x - 15.f * cols + 15.f;
		currentPos.y += 30.f;
	}

	for (int i{}; i < amount; ++i)
	{
		g_pUnit[indexes[i]]->SetMoveLocation(movePositions[i]);
	}
}
#pragma endregion ownDefinitions