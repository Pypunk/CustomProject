#include "pch.h"
#include "Skeleton.h"
#include "Sprite.h"

Skeleton::Skeleton(const Point2f& position)
	:Enemy(position)
{
	m_pIdleSprite = new Sprite{ "Resources/Textures/Character/Skeleton/undead_idle_sheet.png",18,1,1 / 10.f };
	m_pRunSprite = new Sprite{ "Resources/Textures/Character/Skeleton/undead_walk_sheet.png",20,1,1 / 10.f };
}
