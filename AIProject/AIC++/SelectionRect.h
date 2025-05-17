#pragma once
class SelectionRect
{
public:
	SelectionRect(const Rectf worldbounds);
	void CreateRect(const Point2f& mousePos);
	void Draw() const;
	void CreateStartPos(const Point2f& mousePos);
	void RemoveRect();

	Rectf GetRect() const;
	bool IsActive() const;
private:
	Rectf m_Shape;
	Point2f m_StartPos;
	bool m_isMousePressed;
	Rectf m_WorldBounds;
	float Snap(float value, float gridsize);
	float Clamp(float value, float min, float max);
};

