#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	CreateGrid();
}
void Draw()
{
	ClearBackground(0,0,0);
	DrawGrid();
}
void Update(float elapsedSec)
{
	CheckWinStates();
}
void End()
{
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_r:
		ResetGrid();
		break;
	}
}
void OnKeyUpEvent(SDL_Keycode key)
{
}
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MousePos = Point2f{ float( e.x ), float( g_WindowHeight - e.y ) };
}
void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		UpdateGrid();
		break;
	}
}
void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void CreateGrid()
{
	std::cout << "Click the squares to place your symbol\nPlayer 1 is O, player 2 is X"
		<< "\nThe player that manages to get his symbol 3 times in a row, wins the game\n"
		<< "Press R to restart the game\n";

	float xPos{ g_WindowWidth / 2 - 50.f * cols / 2 };
	float yPos{ g_WindowHeight / 2 - 50.f * rows / 2 };
	float width{ 50.f };
	for (int i{}; i < cols; i++)
	{
		for (int j{}; j < rows; j++)
		{
			g_Rect[i][j].left = xPos;
			g_Rect[i][j].bottom = yPos;
			g_Rect[i][j].width = width;
			g_Rect[i][j].height = width;
			yPos += width;
			g_State[i][j] = RectState::unclicked;
		}
		xPos += width;
		yPos = g_WindowHeight / 2 - 50.f * rows / 2;
	}
}

void DrawGrid()
{
	for (int i{}; i < cols; i++)
	{
		for (int j{}; j < rows; j++)
		{
			switch (g_State[i][j])
			{
			case RectState::o:
				SetColor(1, 1, 1);
				DrawRect(g_Rect[i][j]);
				CreateO(20.f, g_Rect[i][j]);
				break;
			case RectState::x:
				SetColor(1, 1, 1);
				DrawRect(g_Rect[i][j]);
				CreateX(45.f, g_Rect[i][j]);
				break;
			case RectState::unclicked:
				SetColor(1, 1, 1);
				DrawRect(g_Rect[i][j]);
				break;
			case RectState::won:
				SetColor(0, 1, 0);
				FillRect(g_Rect[i][j]);
				SetColor(1, 1, 1);
				DrawRect(g_Rect[i][j]);
				break;
			}
		}
	}
}

void ResetGrid()
{
	for (int i{}; i < cols; i++)
	{
		for (int j{}; j < rows; j++)
		{
			g_State[i][j] = RectState::unclicked;
		}
	}
	g_IsGameDone = false;
	Player1 = true;
}

void UpdateGrid()
{
	if (!g_IsGameDone)
	{
		for (int i{}; i < cols; i++)
		{
			for (int j{}; j < rows; j++)
			{
				if (IsPointInRect(g_MousePos, g_Rect[i][j]))
				{
					switch (g_State[i][j])
					{
					case RectState::unclicked:
						if (Player1)
						{
							g_State[i][j] = RectState::o;
							Player1 = !Player1;
						}
						else
						{
							g_State[i][j] = RectState::x;
							Player1 = !Player1;
						}
						break;
					}
				}
			}
		}
	}
}

void CreateO(float radius, const Rectf& rect)
{
	Ellipsef newCircle{};
	newCircle.center = Point2f{ rect.left + 25.f, rect.bottom + 25.f };
	newCircle.radiusX = radius;
	newCircle.radiusY = radius;
	DrawEllipse(newCircle);
}

void CreateX(float lenght, const Rectf& rect)
{
	Point2f bottomLeftPoint{rect.left,rect.bottom};
	Point2f topLeftPoint{rect.left+lenght,rect.bottom+lenght};
	Point2f bottomRightPoint{ rect.left + lenght,rect.bottom };
	Point2f topRightPoint{ rect.left,rect.bottom + lenght };
	DrawLine(bottomLeftPoint, topLeftPoint);
	DrawLine(bottomRightPoint, topRightPoint);
}

void CheckWinStates()
{
	if (checkForWinO(g_State))
	{
		std::cout << "\nCongratulations!\nPlayer 1 Won!\n";
		g_IsGameDone = true;
	}
	if (checkForWinX(g_State))
	{
		std::cout << "\nCongratulations!\nPlayer 2 Won!\n";
		g_IsGameDone = true;
	}
}

bool checkColumnsForO(RectState states[cols][rows])
{
	for (int i{}; i < cols; i++)
	{
		for (int j{}; j < rows; j++)
		{
			if ((states[j][i] == states[j+1][i]) && (states[j+1][i] == states[j+2][i] && states[j][i] == RectState::o))
			{
				states[j][i] = RectState::won;
				states[j + 1][i] = RectState::won;
				states[j + 2][i] = RectState::won;
				return true;
			}
		}
	}
return false;
}

bool checkRowsForO(RectState states[cols][rows])
{
	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < cols; j++)
		{
			if ((states[i][j] == states[i][j + 1]) && (states[i][j + 1] == states[i][j + 2] && states[i][j] == RectState::o))
			{
				states[i][j] = RectState::won;
				states[i][j + 1] = RectState::won;
				states[i][j + 2] = RectState::won;
				return true;
			}
		}
	}
	return false;
}

bool checkDiagonalForO(RectState states[cols][rows])
{
	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < cols; j++)
		{
			if ((states[i][j] == states[i + 1][j + 1]) && (states[i + 1][j + 1] == states[i + 2][j + 2]) && states[i][j] == RectState::o)
			{
				states[i][j] = RectState::won;
				states[i + 1][j + 1] = RectState::won;
				states[i + 2][j + 2] = RectState::won;
				return true;
			}
			if ((states[i][j] == states[i + 1][j - 1]) && (states[i + 1][j - 1] == states[i + 2][j - 2]) && states[i][j] == RectState::o)
			{
				states[i][j] = RectState::won;
				states[i + 1][j - 1] = RectState::won;
				states[i + 2][j - 2] = RectState::won;
				return true;
			}
		}
	}
	return false;
}

bool checkForWinO(RectState states[cols][rows])
{
	bool win = false;
	if (checkColumnsForO(states) || checkRowsForO(states) || checkDiagonalForO(states))
	{
		win = true;
		return win;
	}
	return win;
}

bool checkColumnsForX(RectState states[cols][rows])
{
	for (int i{}; i < cols; i++)
	{
		for (int j{}; j < rows; j++)
		{
			if ((states[j][i] == states[j + 1][i]) && (states[j + 1][i] == states[j + 2][i] && states[j][i] == RectState::x))
			{
				states[j][i] = RectState::won;
				states[j + 1][i] = RectState::won;
				states[j + 2][i] = RectState::won;
				return true;
			}
		}
	}
	return false;
}

bool checkRowsForX(RectState states[cols][rows])
{
	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < cols; j++)
		{
			if ((states[i][j] == states[i][j + 1]) && (states[i][j + 1] == states[i][j + 2] && states[i][j] == RectState::x))
			{
				states[i][j] = RectState::won;
				states[i][j + 1] = RectState::won;
				states[i][j + 2] = RectState::won;
				return true;
			}
		}
	}
	return false;
}

bool checkDiagonalForX(RectState states[cols][rows])
{
	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < cols; j++)
		{
			if ((states[i][j] == states[i + 1][j + 1]) && (states[i + 1][j + 1] == states[i + 2][j + 2]) && states[i][j] == RectState::x)
			{
				states[i][j] = RectState::won;
				states[i + 1][j + 1] = RectState::won;
				states[i + 2][j + 2] = RectState::won;
				return true;
			}
			if ((states[i][j] == states[i+1][j-1]) && (states[i+1][j-1] == states[i+2][j-2]) && states[i][j] == RectState::x)
			{
				states[i][j] = RectState::won;
				states[i + 1][j - 1] = RectState::won;
				states[i + 2][j - 2] = RectState::won;
				return true;
			}
		}
	}
	return false;
}

bool checkForWinX(RectState states[cols][rows])
{
	bool win = false;
	if (checkColumnsForX(states) || checkRowsForX(states) || checkDiagonalForX(states))
	{
		win = true;
		return win;
	}
	return win;
}
#pragma endregion ownDefinitions