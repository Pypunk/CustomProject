#pragma once
#include "GameObject.h"
class Texture;
class Foliage : public GameObject
{
public:
	enum class Type
	{
		Tree = 1,
		Bush = 2,
		Flower = 3
	};
	Foliage(const Point2f& position, int typeId);
	virtual ~Foliage();
	
	virtual void Update(float elapsedSec);
	virtual void Draw() const override;
	void SetToShaking(const Rectf& rect);
private:
	Type m_CurrentType;
	float m_Angle;
	bool m_IsShaking;
	float m_Counter{};
	bool isRotatingLeft{};
};

