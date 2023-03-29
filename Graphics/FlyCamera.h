#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"

class FlyCamera : public CameraBase
{
	
public:
	FlyCamera();
	~FlyCamera() {};

	void Update(float deltaTIme);

protected:
	float m_theta;
	float m_phi;

	float m_turnSpeed = glm::radians(180.f);

	glm::vec3 m_position;

	glm::vec2 m_lastMouse;
	float m_moveSpeed;
};

