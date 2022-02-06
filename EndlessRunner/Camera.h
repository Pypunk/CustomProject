#pragma once
#include "structs.h"
class Camera
{
public:
	Camera(float width, float height);
	void Transform(const Rectf& target) const;
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	
private:			
	float m_Width;
	float m_Height; 
	Rectf m_LevelBoundaries;

	void Clamp(Rectf&  bottomLeftPos) const;

	Rectf Track(const Rectf& target) const;
};

