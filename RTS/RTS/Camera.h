#pragma once
#include "structs.h"
class Camera
{
public:
	Camera(float width, float height);
	void Draw(const Rectf& target);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Rectf GetLevelBoundaries();
	Point2f GetCameraBottomPos(float offsetX = 0.f, float offsetY = 0.f) const;

private:			
	float m_Width;
	float m_Height; 
	Rectf m_LevelBoundaries;
	Rectf m_CameraShape;

	void Clamp(Rectf&  bottomLeftPos) const;

	Rectf Track(const Rectf& target) const;
};

