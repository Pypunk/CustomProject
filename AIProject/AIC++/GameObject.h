#pragma once
#include <memory>
class GameObject
{
public:
	enum class GameObjectType { Unit, Building, Resource, Projectile, Decoration, Neutral };
	GameObject(const Point2f& position, float width, float height);
	virtual ~GameObject() = default;

	virtual void Draw() const;
	virtual void DrawExtra() const = 0;
	virtual void Update(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec) = 0;

	virtual const Rectf& GetShape() const;
	Point2f GetCenter() const;
	bool IsSelected() const;

	void SetSelected(const Point2f& mousePos, const Rectf& selectionRect);
	void AvoidOverlapWithOthers(std::vector<std::unique_ptr<GameObject>>& other, float elapsedSec);
	bool IsPointBlocked(const Point2f& point, std::vector<std::unique_ptr<GameObject>>& other, float blockRadius = 25.f) const;

	virtual GameObjectType GetType() const = 0;
protected:
	Rectf m_Shape;
	float m_Angle;
	Vector2f m_ForwardVector;
	Rectf m_MaxHealth;
	Rectf m_CurrentHealth;
private:
	bool m_IsSelected;
};

