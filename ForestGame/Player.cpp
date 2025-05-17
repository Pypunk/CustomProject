#include "pch.h"
#include "Player.h"
#include "Sprite.h"
#include "GameObject.h"

static const float animationSpeed{ 1 / 5.f };
static const float moveSpeed{ 100.f };

Player::Player(const Point2f& position)
	: Character{position}
{
	m_pRunSprite = std::make_unique<Sprite>(Sprite{ "Resources/Textures/Character/Player/Run.png",4,1,1 / 5.f });
	m_pIdleSprite = std::make_unique<Sprite>(Sprite{ "Resources/Textures/Character/Player/Idle.png",2,1,1 / 5.f });
}

void Player::Update(float elapsedSec)
{
	HandleInput();
	Character::Update(elapsedSec);
}

void Player::HandleInput()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
	m_CurrentState = State::idle;

	if (pStates[SDL_SCANCODE_D])
	{
		m_Velocity.x = moveSpeed;
		m_CurrentState = State::running;
		m_pRunSprite->Flip(true);
		m_pIdleSprite->Flip(true);
	}
	if (pStates[SDL_SCANCODE_A])
	{
		m_Velocity.x = -moveSpeed;
		m_CurrentState = State::running;
		m_pRunSprite->Flip(false);
		m_pIdleSprite->Flip(false);
	}
	if (pStates[SDL_SCANCODE_W])
	{
		m_Velocity.y = moveSpeed;
		m_CurrentState = State::running;
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Velocity.y = -moveSpeed;
		m_CurrentState = State::running;
	}
}
