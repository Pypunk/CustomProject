#pragma once
using namespace utils;
class Spaceship;
class Asteroid
{
public:
	Asteroid(const Point2f& position, float radius, Spaceship* ship);
	~Asteroid();
	void Draw();
	void Update(float elapsedSec);
	const Circlef GetShape();
	const Vector2f GetVelocity();
private:
	Circlef m_Shape;
	Texture m_Texture;
	Vector2f m_Velocity;

	void SetRandXVelocity(int maxSpeed, Spaceship* ship);
	void SetRandYVelocity(int maxSpeed, Spaceship* ship);
};

