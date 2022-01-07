#include "pch.h"
#include "Sprite.h"
#include "utils.h"

Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale)
	:m_Cols{nrCols}
	,m_Rows{nrRows}
	,m_FrameSec{frameSec}
	,m_Scale{scale}
	,m_AccuSec{0}
	,m_ActFrame{0}
{
	TextureFromFile(filename, m_Texture);
}

Sprite::~Sprite()
{
	DeleteTexture(m_Texture);
}

void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		++m_ActFrame %= (m_Cols*m_Rows);
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw(const Point2f& pos)
{
	Rectf srcRect{};
	srcRect.width = GetFrameWith();
	srcRect.height = GetFrameHeight();
	if (m_Rows > 1)
	{
		srcRect.left = (m_ActFrame % m_Cols) * srcRect.width;
		srcRect.bottom = (m_ActFrame / m_Rows + 1) * srcRect.height;
	}
	else
	{
		srcRect.left = m_ActFrame * srcRect.width;
		srcRect.bottom = srcRect.height;
	}

	Rectf destRect{};
	destRect.bottom = pos.y;
	destRect.left = pos.x;
	destRect.width = srcRect.width * m_Scale;
	destRect.height = srcRect.height * m_Scale;

	DrawTexture(m_Texture, destRect, srcRect);
}

float Sprite::GetFrameWith()
{
	return m_Texture.width/m_Cols;
}

float Sprite::GetFrameHeight()
{
	return m_Texture.height/m_Rows;
}
