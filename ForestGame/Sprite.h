#pragma once
class Texture;
class Sprite
{
public:
	Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale = 1.f);
	~Sprite();
	Sprite(const Sprite& other);
	Sprite(Sprite&& other) noexcept;
	Sprite& operator=(const Sprite& other);
	Sprite& operator=(Sprite&& other) noexcept;

	void Update(float elapsedSec);
	void Draw(const Point2f& pos);
	void Draw(const Rectf& dstRect);
	float GetFrameWith();
	float GetFrameHeight();

	void SetRow(int newRow);
	void Flip(bool isFlipped);
	void Reset();
private:
	Texture* m_pTexture;
	std::string m_TextString;
	int m_Cols;
	int m_CurrentRow;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int m_ActFrame;
	float m_Scale;
	bool m_IsFlipped;
};

