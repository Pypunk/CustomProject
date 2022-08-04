#include "pch.h"
#include "Forest.h"

Forest::Forest(const Point2f& center, float size)
{
	int amountOfTrees{ utils::GetRand(1,20) };
	for (int i{}; i < amountOfTrees; ++i)
	{
		m_Trees.push_back(Tree{ utils::GetRandPointInRadius(center,size) });
	}
}

void Forest::Draw() const
{
	for (const Tree& i : m_Trees)
	{
		i.Draw();
	}
}

Tree Forest::GetTree() const
{
	for (const Tree& i : m_Trees)
	{
		return i;
	}
	return Tree(Point2f{});
}
