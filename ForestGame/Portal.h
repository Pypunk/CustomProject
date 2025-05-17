#pragma once
#include "GameObject.h"
#include <memory>

class Player;
class Portal :
    public GameObject
{
public:
    Portal(const Point2f& position);
    void Draw() const override;
    bool IsPlayerOverLapping(std::shared_ptr<Player> player);
    void ToggleActive();
private:
    bool m_IsActive;
};

