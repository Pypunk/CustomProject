#pragma once
using namespace utils;
class Sprite
{
public:
	Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale);
	~Sprite();
	void Update(float elapsedSec);
	void Draw(const Point2f& pos);
	float GetFrameWith();
	float GetFrameHeight();
private:
	Texture m_Texture;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int m_ActFrame;
	float m_Scale;
};

