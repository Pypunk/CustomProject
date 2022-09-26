#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale)
	:m_Cols{nrCols}
	,m_Rows{nrRows}
	,m_FrameSec{frameSec}
	,m_Scale{scale}
	,m_AccuSec{0}
	,m_ActFrame{0}
	, m_CurrentRow{1}
	,m_IsFlipped{false}
	,m_TextString{filename}
	,m_pTexture{new Texture{filename}}
{
}

Sprite::~Sprite()
{
	delete m_pTexture;
}

Sprite::Sprite(const Sprite& other)
	:m_Cols{other.m_Cols}
	,m_Rows{other.m_Rows}
	,m_FrameSec{other.m_FrameSec}
	,m_Scale{other.m_Scale}
	,m_AccuSec{other.m_AccuSec}
	,m_ActFrame{other.m_ActFrame}
	,m_CurrentRow{other.m_CurrentRow}
	,m_IsFlipped{other.m_IsFlipped}
	,m_TextString{other.m_TextString}
{
	m_pTexture = new Texture{ m_TextString };
}

Sprite::Sprite(Sprite&& other) noexcept
	:m_Cols{ other.m_Cols }
	, m_Rows{ other.m_Rows }
	, m_FrameSec{ other.m_FrameSec }
	, m_Scale{ other.m_Scale }
	, m_AccuSec{ other.m_AccuSec }
	, m_ActFrame{ other.m_ActFrame }
	, m_CurrentRow{ other.m_CurrentRow }
	, m_IsFlipped{ other.m_IsFlipped }
	, m_pTexture{ other.m_pTexture }
{
	other.m_Cols = 0;
	other.m_Rows = 0;
	other.m_FrameSec = 0;
	other.m_Scale = 0;
	other.m_ActFrame = 0;
	other.m_AccuSec = 0;
	other.m_CurrentRow = 0;
	other.m_IsFlipped = false;
	other.m_pTexture = nullptr;
}

Sprite& Sprite::operator=(const Sprite& other)
{
	m_Cols = other.m_Cols;
	m_Rows = other.m_Rows;
	m_FrameSec = other.m_FrameSec;
	m_Scale = other.m_Scale;
	m_ActFrame = other.m_ActFrame;
	m_AccuSec = other.m_AccuSec;
	m_CurrentRow = other.m_CurrentRow;
	m_IsFlipped = other.m_IsFlipped;
	m_TextString = other.m_TextString;
	delete m_pTexture;
	m_pTexture = new Texture{ m_TextString };
	return *this;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	m_Cols = other.m_Cols;
	m_Rows = other.m_Rows;
	m_FrameSec = other.m_FrameSec;
	m_Scale = other.m_Scale;
	m_ActFrame = other.m_ActFrame;
	m_AccuSec = other.m_AccuSec;
	m_CurrentRow = other.m_CurrentRow;
	m_IsFlipped = other.m_IsFlipped;
	delete m_pTexture;
	m_pTexture = other.m_pTexture;

	other.m_Cols = 0;
	other.m_Rows = 0;
	other.m_FrameSec = 0;
	other.m_Scale = 0;
	other.m_ActFrame = 0;
	other.m_AccuSec = 0;
	other.m_CurrentRow = 0;
	other.m_IsFlipped = false;
	other.m_pTexture = nullptr;

	return *this;
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

	srcRect.left = m_ActFrame * srcRect.width;
	srcRect.bottom = srcRect.height * m_CurrentRow;

	Rectf destRect{};
	destRect.bottom = pos.y;
	destRect.left = pos.x;
	destRect.width = srcRect.width * m_Scale;
	destRect.height = srcRect.height * m_Scale;

	m_pTexture->Draw(destRect, srcRect);
}

void Sprite::Draw(const Rectf& dstRect)
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
		srcRect.bottom = srcRect.height * m_CurrentRow;
	}
	if (m_IsFlipped)
	{
		const Rectf newPos{ -dstRect.left-dstRect.width,dstRect.bottom,dstRect.width,dstRect.height };
		glPushMatrix();
		glScalef(-1, 1, 1);
		m_pTexture->Draw(newPos, srcRect);
		glPopMatrix();
	}
	else
	{
		m_pTexture->Draw(dstRect, srcRect);
	}
}

float Sprite::GetFrameWith()
{
	return m_pTexture->GetWidth() / m_Cols;
}

float Sprite::GetFrameHeight()
{
	return m_pTexture->GetHeight() / m_Rows;
}

void Sprite::SetRow(int newRow)
{
	m_CurrentRow = newRow;
}

void Sprite::Flip(bool isFlipped)
{
	m_IsFlipped = isFlipped;
}

void Sprite::Reset()
{
	m_ActFrame = 0;
	m_CurrentRow = 1;
}
