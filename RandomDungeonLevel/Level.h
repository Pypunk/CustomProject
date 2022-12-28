#pragma once
#include <set>
class Level
{
public:
	Level(const Window& window);
	~Level();

	void Draw() const;
	void ResetGame(const Window& window);
	void AddTile(const Point2f& mousePos);
private:
	int m_Rows{};
	int m_Cols{};
	std::set<class Tile*> m_pTiles;
	std::vector<Rectf> m_Rects;
	std::vector<bool> m_IsRectFilled;
};

