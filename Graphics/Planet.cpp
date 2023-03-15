#include "Planet.h"
#include "GraphicsApp.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Input.h"


Planet::Planet(bool hasRing, bool isMoon, float speed, glm::vec3 position, float radius, int rows, int columns, glm::vec4 color)
{
	m_position = position;
	m_radius = radius;
	m_rows = rows;
	m_columns = columns;
	m_color = color;
	m_hasRing = hasRing;
	m_speed = speed;
	m_transform = glm::mat4(1);
}

Planet::~Planet()
{
}

void Planet::Draw()
{
	aie::Gizmos::addSphere(m_position, m_radius, m_rows, m_columns, m_color, &m_transform);

	if (m_hasRing)
	{
		aie::Gizmos::addRing(m_position, m_radius + 0.5, m_radius + 1, 12, m_color, &m_transform);
	}


}

void Planet::Update(float deltaTime)
{
	glm::vec3 rotPoint;
	if (!m_isMoon)
	{
		rotPoint = m_position;
	}
	else
	{
		rotPoint = m_parent->GetPosition();
	}
		

	m_transform = glm::translate(m_transform, -rotPoint);
	m_transform = glm::rotate(m_transform, 0.01f * m_speed, glm::vec3(0, 1, 0));
	m_transform = glm::translate(m_transform, rotPoint);



}

