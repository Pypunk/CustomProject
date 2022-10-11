#include "pch.h"
#include "Player.h"
#include "Sprite.h"
#include "GameObject.h"

Player::Player(const Point2f& position)
	: Character{position}
{
	m_pRunSprite = new Sprite{ "Resources/Textures/Character/Player/Run.png",4,1,1 / 5.f };
	m_pIdleSprite = new Sprite{ "Resources/Textures/Character/Player/Idle.png",2,1,1 / 5.f };
}

void Player::Update(float elapsedSec)
{
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
	m_CurrentState = State::idle;
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_D] )
	{
		m_Velocity.x = m_MoveSpeed;
		m_CurrentState = State::running;
		m_pRunSprite->Flip(true);
		m_pIdleSprite->Flip(true);
	}
	if (pStates[SDL_SCANCODE_A])
	{
		m_Velocity.x = -m_MoveSpeed;
		m_CurrentState = State::running;
		m_pRunSprite->Flip(false);
		m_pIdleSprite->Flip(false);
	}
	if (pStates[SDL_SCANCODE_W])
	{
		m_Velocity.y = m_MoveSpeed;
		m_CurrentState = State::running;
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Velocity.y = -m_MoveSpeed;
		m_CurrentState = State::running;
	}
	Character::Update(elapsedSec);
}
