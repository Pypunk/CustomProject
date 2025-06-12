#pragma once
#include "GameObject.h"
class Building :
    public GameObject
{
public:
    enum class BuildingType
    {
        TownCenter,
        Barracks,
        ArcheryRange,
        Stables,
    };
    Building(const Point2f& position);

    GameObjectType GetType() const override;

    void Draw() const override;
    void DrawExtra() const override;
    void Update(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec) override;
    void AddProgress(float progress);
    std::unique_ptr<class Unit> CreateUnit(Point2f position, BuildingType type);
    void SetRallyPoint(const Point2f& point);
    void SetCenter(const Point2f& center);

    virtual BuildingType GetBuildingType() const = 0;
    bool IsProductionFinished() const;
    void ResetProduction();
    void StartProduction(int amount);
    virtual ResourceCost GetCost() const = 0;
protected:
    Rectf m_ProgressBar;
    Rectf m_ProgressFill;
    float m_ProductionSpeed;
    ResourceCost m_Price;
private:
    Point2f m_RallyPoint;
    Point2f GetRallyPoint();
    int m_ProductionAmount;
};

