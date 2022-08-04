#pragma once
#include <vector>
#include "Tree.h"
class Forest
{
public:
	Forest(const Point2f& center, float size);
	void Draw() const;
	Tree GetTree() const;
private:
	std::vector<Tree> m_Trees;
};

