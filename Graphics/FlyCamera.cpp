#include "FlyCamera.h"
#include <glm/ext.hpp>
#include "Input.h"


FlyCamera::FlyCamera() 
{
	m_position = glm::vec3(-10, 2, 0);
	m_phi = 0;
	m_theta = 0;
	m_moveSpeed = 1;
}

void FlyCamera::Update(float deltaTIme)
{
  	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);


	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR) * glm::sin(thetaR));
	glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
	glm::vec3 up(0, 1, 0);

	// WASD to Move, QE to go Up and Down

	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_position += forward * deltaTIme * m_moveSpeed;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_position -= forward * deltaTIme * m_moveSpeed;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_position -= right * deltaTIme * m_moveSpeed;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_position += right * deltaTIme * m_moveSpeed;

	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_position += up * deltaTIme * m_moveSpeed;
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_position -= up * deltaTIme * m_moveSpeed;

	m_moveSpeed = input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) ? 4 : 1;
	// Get the nouse coordinates
	float mx = input->getMouseX();
	float my = input->getMouseY();

	// If the right button is held down, increment theta and phi (rotate)
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += m_turnSpeed * (mx - m_lastMouse.x) * deltaTIme;
		m_phi += m_turnSpeed * (my - m_lastMouse.y) * deltaTIme;
	}

	m_lastMouse = glm::vec2(mx, my);

}


