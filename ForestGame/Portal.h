#pragma once
#include "GameObject.h"
class Player;
class Portal :
    public GameObject
{
public:
    Portal(const Point2f& position);
    void Draw() const override;
    bool IsPlayerOverLapping(const Player* player);
    void ToggleActive();
private:
    bool m_IsActive;
};

