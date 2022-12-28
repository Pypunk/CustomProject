#pragma once
class Tile
{
public:
	Tile(const Rectf& positionRect, int index);
	~Tile();

	void Draw() const;
	int GetIndex() const;
	Rectf GetShape() const;
private:
	int m_Index;
	Rectf m_Shape;
	class Texture* m_pTexture;
};

