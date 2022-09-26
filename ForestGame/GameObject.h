#pragma once
class Texture;
class GameObject
{
public:
	GameObject(const Point2f& position);
	virtual ~GameObject();

	virtual void Draw() const;
	Rectf GetCollisionShape() const;
	Rectf GetShape() const;
	bool GetPassable() const;

protected:
	Rectf m_Shape;
	Texture* m_pTexture;
	float m_ZIndex;
	bool m_IsPassable;
};

