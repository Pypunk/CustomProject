#pragma once
class GameObject
{
public:
	enum class GameObjectType { Unit, Building, Resource, Projectile, Decoration, Neutral };
	GameObject(const Point2f& position, float width, float height);
	virtual ~GameObject() = default;

	virtual void Draw() const;
	virtual void DrawExtra() const = 0;
	virtual void Update(std::vector<GameObject*>& other, float elapsedSec) = 0;

	const Rectf& GetShape() const;
	Point2f GetCenter() const;
	bool IsSelected() const;

	void SetSelected(const Point2f& mousePos, const Rectf& selectionRect);
	void AvoidOverlapWithOthers(const std::vector<GameObject*>& others, float elapsedSec);
	bool IsPointBlocked(const Point2f& point, const std::vector<GameObject*>& others, float blockRadius = 25.f) const;

	virtual GameObjectType GetType() const = 0;
protected:
	Rectf m_Shape;
	float m_Angle;
	Vector2f m_ForwardVector;
private:
	bool m_IsSelected;
};

