#pragma once
#include "Enemy.h"
class Skeleton :
    public Enemy
{
public:
    Skeleton(const Point2f& position);

    Rectf GetDamageShape() const;
private:
    Rectf m_DamageShape;
};

