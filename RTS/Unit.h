#pragma once
using namespace utils;
class Unit
{
public:
	Unit(const Point2f& position, float size);
	const void Draw();
	void MoveTo(float elapsedSec);
	bool SelectUnit(const Point2f& mousePos);
	bool SelectUnit(const Rectf& selectionRect);
	void SetMoveLocation(const Point2f& newLocation);
	const Rectf GetShape();
	void Deselect();
private:

	enum class UnitState
	{
		selected,
		deselected,
	};
	UnitState m_state;
	Rectf m_Shape;
	Point2f m_MoveLocation;
};

