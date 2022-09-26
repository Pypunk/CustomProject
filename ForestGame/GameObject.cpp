#include "pch.h"
#include "GameObject.h"
#include "Texture.h"
#include "Player.h"

GameObject::GameObject(const Point2f& position)
	:m_Shape{position,0.f,0.f}
	,m_pTexture{nullptr}
	,m_ZIndex{0}
	,m_IsPassable{true}
{
}

GameObject::~GameObject()
{
	delete m_pTexture;
}


void GameObject::Draw() const
{
	if (m_pTexture)
	{
		m_pTexture->Draw(m_Shape);
	}
}


Rectf GameObject::GetCollisionShape() const
{
	return Rectf{ m_Shape.GetBottomLeft(m_Shape.width/4.f),m_Shape.width/2.f,m_Shape.height/4.f };
}

Rectf GameObject::GetShape() const
{
	return m_Shape;
}

bool GameObject::GetPassable() const
{
	return m_IsPassable;
}
