#include "pch.h"
#include "Portal.h"
#include "Player.h"
#include "Texture.h"

Portal::Portal(const Point2f& position)
	:GameObject{position}
	,m_IsActive{false}
{
	m_pTexture = std::make_unique<Texture>("Resources/Textures/Portal/Portal.png");
	m_Shape.width = 50.f;
	m_Shape.height = 100.f;
}

void Portal::Draw() const
{
	if (m_IsActive)
	{
		GameObject::Draw();
	}
}


bool Portal::IsPlayerOverLapping(std::shared_ptr<Player> player)
{
	return utils::IsOverlapping(player->GetCollisionShape(), GetCollisionShape()) && m_IsActive;
}

void Portal::ToggleActive()
{
	m_IsActive = !m_IsActive;
}

