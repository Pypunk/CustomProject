#include "pch.h"
#include "Character.h"
#include "Platform.h"
#include "Sprite.h"

Character::Character(const Point2f& position, float size)
	:m_Shape{ position.x,position.y,size,size }
	,m_Gravity{9.81f}
	,m_Jumping{false}
	,m_State{CharacterState::standing}
	,m_pSprite{new Sprite{"Sprites/RunningKnight.png",8,1,1/15.f,2}}
{
}

Character::~Character()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

void Character::Draw()
{
	switch (m_State)
	{
	case Character::CharacterState::jumping:
		SetColor(1, 0, 0, 1);
		break;
	case Character::CharacterState::running:
		SetColor(0, 1, 0, 1);
		break;
	case Character::CharacterState::standing:
		SetColor(0, 0, 1, 1);
		break;
	}
	FillRect(m_Shape);
	Point2f spritePos{ m_Shape.left,m_Shape.bottom - 5.f };
	m_pSprite->Draw(spritePos);
}

void Character::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec);
	m_Velocity.y -= m_Gravity;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	m_State = CharacterState::standing;
	if (m_Jumping)
	{
		m_Shape.bottom += 500.f * elapsedSec;
		m_State = CharacterState::jumping;
	}
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
	{
		m_Shape.left += 200.f * elapsedSec;
		m_State = CharacterState::running;
	}
	if ( pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
	{
		m_Shape.left -= 200.f * elapsedSec;
		m_State = CharacterState::running;
	}
}

void Character::UpdateCollision(Platform& platform)
{
	if (platform.IsOnPlatform(m_Shape))
	{
		m_Velocity.y = 0.f;
		m_Shape.bottom = platform.GetTop();
		m_Jumping = false;
	}
}

const Rectf Character::GetShape()
{
	return m_Shape;
}

void Character::Jump()
{
	m_Jumping = true;
}
