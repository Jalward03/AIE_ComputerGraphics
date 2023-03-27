#pragma once
#include "CameraBase.h"

class StationaryCamera : public CameraBase
{
public:
	StationaryCamera();
	~StationaryCamera() {};
	void SetPosition(glm::vec3 position) { m_position = position; }
	glm::vec3 GetPosition() { return m_position; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float width, float height);
	glm::mat4 GetTransform(glm::vec3 position,
		glm::vec3 eularAngles, glm::vec3 scale);
	virtual void Update(float deltaTIme);

protected:
	float m_theta;
	float m_phi;

	float m_turnSpeed = glm::radians(180.f);

	glm::vec3 m_position;

	glm::vec2 m_lastMouse;
	float m_moveSpeed;
};

