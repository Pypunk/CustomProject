#include "pch.h"
#include "Tree.h"

Tree::Tree(const Point2f& position)
	:m_Shape{position,50,50}
	,m_IsClickedOn{false}
{
}

void Tree::Draw() const
{
	utils::SetColor(Color4f{ 0,1,0,1 });
	utils::DrawRect(m_Shape);
}

void Tree::SetClickedOn()
{
	m_IsClickedOn = true;
}

Rectf Tree::GetShape() const
{
	return m_Shape;
}
