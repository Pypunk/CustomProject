#pragma once
class Button
{
public:
	Button(const Point2f& position, float width, float height);

	void Draw(const Point2f& mousePos) const;
	bool ButtonClicked(const Point2f& mousePos) const;
	Rectf GetShape() const;
private:
	Rectf m_Shape;
};

