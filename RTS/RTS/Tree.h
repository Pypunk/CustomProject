#pragma once
class Tree
{
public:
	Tree(const Point2f& position);
	void Draw() const;
	void SetClickedOn();

	Rectf GetShape() const;
private:
	Rectf m_Shape;
	bool m_IsClickedOn;
};

