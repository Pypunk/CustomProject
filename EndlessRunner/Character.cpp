#include "pch.h"
#include "Character.h"
#include "utils.h"
#include "Sprite.h"
#include "Tile.h"
using namespace utils;

Character::Character(const Point2f& position)
	:m_Shape{position.x,position.y,50,50}
	,m_Gravity{-9.81f}
	,m_Velocity{}
	,m_pTexture{new Sprite{"Resources/adventurer-run3-sword-Sheet.png",6,1,1/10.f,2}}
{
}

Character::~Character()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

const void Character::Draw()
{
	Point2f shapePos{ m_Shape.left - m_Shape.width / 2.f,m_Shape.bottom - 5.f };
	m_pTexture->Draw(shapePos);
}

void Character::Update(float elapsedSec)
{
	m_Velocity.y += m_Gravity;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	float jumpSpeed{ 300.f };
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if (m_CurrentState == State::jumping)
	{
		m_Shape.bottom += jumpSpeed * elapsedSec;
	}
	m_pTexture->Update(elapsedSec);
}

void Character::Jump()
{
	m_CurrentState = State::jumping;
}

void Character::DoPlatformCollision(Tile* tile)
{
	std::vector<Point2f> tileTopPoints{ Point2f{tile->GetShape().left,tile->GetShape().bottom + tile->GetShape().height},
										Point2f{tile->GetShape().left + tile->GetShape().width,tile->GetShape().bottom + tile->GetShape().height} };
	utils::HitInfo hit{};
	if (!tile->IsSpike())
	{
		if (Raycast(tileTopPoints, Point2f{ m_Shape.left + m_Shape.width / 2.f,m_Shape.bottom },
								   Point2f{ m_Shape.left + m_Shape.width / 2.f,m_Shape.bottom + m_Shape.height }, hit))
		{
			m_Velocity.y = 0.f;
			m_Shape.bottom = hit.intersectPoint.y;
			m_CurrentState = State::onGround;
		}
	}
}
