#pragma once
using namespace utils;
class Platform
{
public:
	Platform(const Point2f& position, float width, float height);
	Platform(const Rectf& rect);

	void Draw();
	bool IsOnPlatform(const Rectf& actor);
	void UpdatePlatform(float xCamPos);
	float GetTop();
	const Rectf GetShape();
private:
	Rectf m_Shape;
};

