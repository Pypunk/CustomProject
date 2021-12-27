#pragma once
using namespace utils;
class SelectionRect
{
public:
	SelectionRect();
	const void Draw();
	void UpdateRect(const Point2f& mousePos);
	void SetFirstPos(const Point2f& position);
	void SetReleased();

	const Rectf GetShape();
private:
	bool m_Pressed;
	Point2f m_FirstPos;
	Rectf m_Shape;
};

