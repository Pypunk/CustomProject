#pragma once
#include "GameObject.h"
class Building :
    public GameObject
{
public:
    Building(const Point2f& position);


    GameObjectType GetType() const override;

    void DrawExtra() const override;
    void Update(std::vector<GameObject*>& other, float elapsedSec) override;
private:

};

