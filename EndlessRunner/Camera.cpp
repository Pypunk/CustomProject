#include "pch.h"
#include "Camera.h"
#include "utils.h"


Camera::Camera(float width, float height):
	m_Width{width},
	m_Height{height},
	m_LevelBoundaries{ Rectf{0,0,0,0} }
{}

void Camera::Transform(const Rectf& target) const{

	Rectf cameraRect{ Track(target) };
	Clamp(cameraRect);
	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	glTranslatef(-cameraRect.left, -cameraRect.bottom, 0);
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries){
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Clamp(Rectf& cameraRect) const{
	if (cameraRect.left < m_LevelBoundaries.left) {
		cameraRect.left = m_LevelBoundaries.left+1;
	}
	if (cameraRect.bottom < m_LevelBoundaries.bottom) {
		cameraRect.bottom = m_LevelBoundaries.bottom+1;
	}
	if (cameraRect.left + cameraRect.width > m_LevelBoundaries.left + m_LevelBoundaries.width) {
		cameraRect.left = m_LevelBoundaries.width - m_Width - 1;
	}
	if (cameraRect.bottom + cameraRect.height > m_LevelBoundaries.bottom + m_LevelBoundaries.height) {
		cameraRect.bottom = m_LevelBoundaries.height - m_Height - 1;
	}
}

Rectf Camera::Track(const Rectf& target) const {
	float left{ (target.left - (m_Width / 2)) + target.width / 2 };
	float bottom{ (target.bottom - (m_Height / 2)) + target.height / 2 };
	return Rectf { left, bottom, m_Width, m_Height };
	
}
