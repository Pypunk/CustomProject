#include "pch.h"
#include "Skeleton.h"
#include "Sprite.h"

Skeleton::Skeleton(const Point2f& position)
	:Enemy(position)
{
	m_pIdleSprite = std::make_unique<Sprite>(Sprite{ "Resources/Textures/Character/Skeleton/undead_idle_sheet.png",18,1,1 / 10.f });
	m_pRunSprite = std::make_unique<Sprite>(Sprite{ "Resources/Textures/Character/Skeleton/undead_walk_sheet.png",20,1,1 / 10.f });
	m_pAttackSprite = std::make_unique<Sprite>(Sprite{ "Resources/Textures/Character/Skeleton/undead_attack_sheet.png",20,1,1 / 15.f });
}

Rectf Skeleton::GetDamageShape() const
{
	return m_DamageShape;
}
