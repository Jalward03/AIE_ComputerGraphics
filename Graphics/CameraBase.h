#pragma once
#include <glm/glm.hpp>

class CameraBase
{
	

public:
	CameraBase();
	~CameraBase() {};
	virtual void Update(float deltaTime);
	glm::vec3 GetPosition() { return m_position; }
	float GetTheta() { return m_theta; }
	float GetPhi() { return m_phi; }
	virtual void SetPosition(glm::vec3 pos) { m_position = pos; }
	virtual void SetRotation(float theta, float phi) 
	{
		m_theta = theta;
		m_phi = phi;

	}
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float width, float height);
	glm::mat4 GetTransform(glm::vec3 position,
		glm::vec3 eularAngles, glm::vec3 scale);
	

protected:
	float m_theta;
	float m_phi;


	glm::vec3 m_position;


};


