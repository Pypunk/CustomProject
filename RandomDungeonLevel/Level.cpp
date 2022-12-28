#include "pch.h"
#include "Level.h"
#include "Tile.h"
#include <iostream>
#include <set>

Level::Level(const Window& window)
	:m_Rows{}
	,m_Cols{}
{
	while (!(m_Cols % 2))
	{
		std::cout << "How many columns do you want? \n";
		std::cin >> m_Cols;
		if (!(m_Cols % 2))
		{
			std::cout << "Must be an odd number\n";
		}
	}
	while (!(m_Rows % 2))
	{
		std::cout << "How many rows do you want? \n";
		std::cin >> m_Rows;
		if (!(m_Rows % 2))
		{
			std::cout << "Must be an odd number\n";
		}
	}
	const float width{ 64.f };
	const float height{ 64.f };
	const float offSetX{ width * m_Cols / 2.f };
	const float offSetY{ height * m_Rows / 2.f };
	Point2f position{ window.width / 2.f-offSetX,window.height / 2.f-offSetY };
	for (int i{}; i < m_Rows; ++i)
	{
		for (int j{}; j < m_Cols; ++j)
		{
			m_Rects.push_back(Rectf{ position,width,height });
			position.x += width;
		}
		position.x = window.width / 2.f - offSetX;
		position.y += height;
	}
	const int midIndex{ m_Rows * m_Cols / 2 };
	for (int i{}; i < m_Rects.size(); ++i)
	{
		m_IsRectFilled.push_back(false);
	}
	m_pTiles.insert(new Tile{ m_Rects[midIndex],1 });
	m_IsRectFilled[midIndex] = true;
}

Level::~Level()
{
	for (const Tile* tile : m_pTiles)
	{
		delete tile;
	}
	m_pTiles.clear();
}

void Level::Draw() const
{
	for (const Tile* tile : m_pTiles)
	{
		if (tile)
		{
			tile->Draw();
		}
	}
	for (const Rectf& rect : m_Rects)
	{
		utils::DrawRect(rect);
	}
}

void Level::ResetGame(const Window& window)
{
	for (const Tile* tile : m_pTiles)
	{
		delete tile;
	}
	m_pTiles.clear();
	const int midIndex{ m_Rows * m_Cols / 2 };
	m_pTiles.insert(new Tile{ m_Rects[midIndex], 1 });
	for (int i{}; i < m_IsRectFilled.size(); ++i)
	{
		m_IsRectFilled[i] = false;
	}
	m_IsRectFilled[midIndex] = true;
}

void Level::AddTile(const Point2f& mousePos)
{	
	for (int i{}; i < m_Rows; ++i)
	{
		for (int j{}; j < m_Cols; ++j)
		{
			if (utils::IsPointInRect(mousePos, m_Rects[utils::GetIndex(i, j, m_Cols)]))
			{
				if (utils::GetIndex(i, j, m_Cols) - m_Cols >= 0 
					&& m_IsRectFilled[utils::GetIndex(i, j, m_Cols) - m_Cols]
					&& !m_IsRectFilled[utils::GetIndex(i,j,m_Cols)])
				{
					m_pTiles.insert(new Tile{ m_Rects[utils::GetIndex(i,j,m_Cols)],utils::GetRand(1,11) });
					m_IsRectFilled[utils::GetIndex(i, j, m_Cols)] = true;
				}
				if (utils::GetIndex(i, j, m_Cols) + m_Cols < (m_Cols * m_Rows) 
					&& m_IsRectFilled[utils::GetIndex(i, j, m_Cols) + m_Cols]
					&& !m_IsRectFilled[utils::GetIndex(i,j,m_Cols)])
				{
					m_pTiles.insert(new Tile{ m_Rects[utils::GetIndex(i,j,m_Cols)],utils::GetRand(1,11) });
					m_IsRectFilled[utils::GetIndex(i, j, m_Cols)] = true;
				}
				if (utils::GetIndex(i, j, m_Cols) - 1 >= 0
					&& m_IsRectFilled[utils::GetIndex(i,j,m_Cols)-1]
					&& !m_IsRectFilled[utils::GetIndex(i,j,m_Cols)])
				{
					m_pTiles.insert(new Tile{ m_Rects[utils::GetIndex(i,j,m_Cols)],utils::GetRand(1,11) });
					m_IsRectFilled[utils::GetIndex(i, j, m_Cols)] = true;
				}
				if (utils::GetIndex(i, j, m_Cols) + 1 < (m_Cols * m_Rows)
					&& m_IsRectFilled[utils::GetIndex(i,j,m_Cols)+1]
					&& !m_IsRectFilled[utils::GetIndex(i,j,m_Cols)])
				{
					m_pTiles.insert(new Tile{ m_Rects[utils::GetIndex(i,j,m_Cols)],utils::GetRand(1,11) });
					m_IsRectFilled[utils::GetIndex(i, j, m_Cols)] = true;
				}
			}
		}
	}
}
