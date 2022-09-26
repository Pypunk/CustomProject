#pragma once
#include "Character.h"
class Enemy :
    public Character
{
public:
    Enemy(const Point2f& position);

    void MoveToPlayer(const Rectf& player);
};

