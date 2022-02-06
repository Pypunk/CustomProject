#pragma once
#include <vector>
class Texture;
class Tile
{
public:
	Tile(const Point2f& position);
	Tile(const Tile& tile);//copy constructor
	Tile(Tile&& tile) noexcept;//move constructor
	~Tile();

	const void Draw();
	void Update(float elapsedSec, float amountOfTiles);
	const Rectf GetShape();
	bool IsSpike();
	void DetectPreviousTile(Tile* previous);
private:
	const int m_AmountOfTextures{ 2 };
	bool m_IsSpike;
	bool m_IsPrevSpike;
	Point2f m_Position;
	std::vector<std::string> textureStrings;
	Texture* m_pTexture;

	void CreateRandomTexture();
};

