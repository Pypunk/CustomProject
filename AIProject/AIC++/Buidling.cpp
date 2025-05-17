#include "pch.h"
#include "Buidling.h"

Building::Building(const Point2f& position)
	:GameObject(position,100.f,100.f)
{
}

GameObject::GameObjectType Building::GetType() const
{
	return GameObject::GameObjectType::Building;
}

void Building::DrawExtra() const
{
}

void Building::Update(std::vector<GameObject*>& other, float elapsedSec)
{
}
