#pragma once
using namespace utils;
class Spaceship
{
public:
	Spaceship(const Point2f& position, float size);
	~Spaceship();
	void Draw();
	void Update(float elapsedSec, float windowWidth, float windowHeight);
	void SetHorVelocity(float speed);
	void SetVertVelocity(float speed);
	const Vector2f GetCurrentVelocity();
	const Rectf GetShape();
	const bool IsHit(const Circlef& asteroidShape);
	const bool IsRocketHit(const Circlef& asteroidShape);
	void SetBulletTarget(const Point2f& position);
private:
	bool m_IsShooting;
	bool m_IsInvincible;
	float m_Time;
	Rectf m_Shape;
	Point2f m_CenterPoint;
	Texture m_Texture;
	Vector2f m_Velocity;
	Circlef m_Rocket;
	Point2f m_TargetPoint;

	void UpdateBottom(float windowHeight);
	void UpdateLeft(float windowWidth);
	void UpdateRocket(float elapsedSec);
};

