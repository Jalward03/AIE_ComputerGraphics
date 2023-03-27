#include "StationaryCamera.h"
#include <glm/ext.hpp>
#include "Input.h"


StationaryCamera::StationaryCamera()
{
	m_position = glm::vec3(-1000, 2, 0);
	m_phi = 0;
	m_theta = 0;
	m_moveSpeed = 1;
}

void StationaryCamera::Update(float deltaTIme)
{


}

glm::mat4 StationaryCamera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR) * glm::sin(thetaR));


	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 StationaryCamera::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, width / height,
		0.1f, 1000.f);
}

glm::mat4 StationaryCamera::GetTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	return glm::mat4();
}
