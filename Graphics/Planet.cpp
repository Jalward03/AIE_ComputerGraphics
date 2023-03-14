#include "Planet.h"
#include "GraphicsApp.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>


Planet::Planet(bool hasRing, float speed, glm::vec3 position, float radius, int rows, int columns, glm::vec4 color, glm::mat4 transform)
{
	m_position = position;
	m_radius = radius;
	m_rows = rows;
	m_columns = columns;
	m_color = color;
	m_hasRing = hasRing;
	m_speed = speed;
	m_transform = transform;
}

Planet::~Planet()
{
}

void Planet::Draw()
{
	aie::Gizmos::addSphere(m_position, m_radius, m_rows, m_columns, m_color, &m_transform);

	if (m_hasRing)
	{
		aie::Gizmos::addRing(m_position, m_radius + 0.5, m_radius + 1, 12, m_color);
	}
}

void Planet::Update(float deltaTime)
{
	
	m_transform = glm::lookAt(glm::vec3(glm::sin(m_time*m_speed) * m_position.x, 0, glm::cos(m_time*m_speed) * m_position.z),
		m_position, glm::vec3(0, 1, 0));

	
}

