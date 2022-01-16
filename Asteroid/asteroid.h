#pragma once
using namespace utils;
class Spaceship;
class Asteroid
{
public:
	Asteroid(const Point2f& position, Spaceship* ship);
	~Asteroid();
	void Draw();
	void Update(float elapsedSec);
	const Circlef GetShape();
	const Vector2f GetVelocity();
private:
	Point2f m_Position;
	Texture m_Texture;
	Vector2f m_Velocity;
	float m_Angle;

	float SetRandXVelocity(int maxSpeed, Spaceship* ship);
	float SetRandYVelocity(int maxSpeed, Spaceship* ship);
};

