#include "CameraBase.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Input.h"


CameraBase::CameraBase()
{
	m_position = glm::vec3(-10, 2, 0);
	m_phi = 0;
	m_theta = 0;
	m_moveSpeed = 1;
}

void CameraBase::Update(float deltaTime)
{

}


glm::mat4 CameraBase::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR) * glm::sin(thetaR));


	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 CameraBase::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, width / height,
		0.1f, 1000.f);
}

glm::mat4 CameraBase::GetTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	return glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.y), glm::vec3(0, 1, 1))
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.x), glm::vec3(1, 0, 1))
		* glm::scale(glm::mat4(1), scale);
		
}

