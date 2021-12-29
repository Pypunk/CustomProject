#pragma once
using namespace utils;
class Health;
class Spaceship
{
public:
	Spaceship(const Point2f& position, float size);
	~Spaceship();
	void Draw(float windowWidth, float windowHeight);
	void Update(float elapsedSec, float windowWidth, float windowHeight);
	void SetHorVelocity(float speed);
	void SetVertVelocity(float speed);
	const Vector2f GetCurrentVelocity();
	const Rectf GetShape();
	const bool IsHit(const Circlef& asteroidShape);
	const bool IsRocketHit(const Circlef& asteroidShape);
	const bool GetInvincible();
	const bool IsDead();
	void SetBulletTarget(const Point2f& position);
	void SetZeroVelocity();
private:
	bool m_IsShooting;
	bool m_IsInvincible;
	float m_Time;
	Rectf m_Shape;
	Point2f m_CenterPoint;
	Texture m_Texture;
	Texture m_HealthText;
	Texture m_InvincibleText;
	Vector2f m_Velocity;
	Circlef m_Rocket;
	Point2f m_TargetPoint;
	Health* m_pHealth;

	void UpdateBottom(float windowHeight);
	void UpdateLeft(float windowWidth);
	void UpdateRocket(float elapsedSec);
};

