#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"

class FlyCamera : public CameraBase
{
	
public:
	FlyCamera();
	~FlyCamera() {};

	void Update(float deltaTIme) override;

protected:
	float m_turnSpeed = glm::radians(180.f);
	glm::vec2 m_lastMouse;
	float m_moveSpeed;
};

