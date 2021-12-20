#pragma once
#include "Unit.h"
class Villager :
    public Unit
{
public:
    Villager(const Point2f& position, float size);
    const void Draw();
private:
    Color4f m_Color;
};

