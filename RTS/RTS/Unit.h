#pragma once
#include "Texture.h"
class Unit
{
public:
	Unit(const Point2f& position, float size);
	virtual void Draw() const;
	void MoveTo(float elapsedSec);
	bool SelectUnit(const Point2f& mousePos);
	bool SelectUnit(const Rectf& selectionRect);
	void SetMoveLocation(const Point2f& newLocation);
	const Rectf GetShape();
	void Deselect();
	void Select();
private:
	enum class UnitState
	{
		selected,
		deselected,
	};
	UnitState m_state;
	Rectf m_Shape;
	Point2f m_MoveLocation;
protected:
	Color4f m_Color;
	Texture m_Text;
};

