#pragma once

#include "Application.h"
#include "Gizmos.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>


class Planet
{

public:
	Planet(bool hasRing, bool isMoon, float speed, glm::vec3 position, float radius, int rows, int columns, glm::vec4 color);
	~Planet();
	void Draw();
	void Update(float deltaTime);
	void SetPosition(glm::vec3 position) { m_position = position; }
	void SetTime(float time) { m_time = time; }
	void SetParent(Planet* parent) { m_parent = parent; }

	glm::vec3 GetPosition() { return m_position; }
	float GetSpeed() { return m_speed; }
    glm::mat4 GetTransform() { return m_transform; }

protected:
	glm::vec3 m_position;
	float m_radius;
	int m_rows;
	int m_columns;
	glm::vec4 m_color;
	glm::mat4 m_transform;
	float m_speed;
	float m_time;
	bool m_hasRing = false;
	bool m_isMoon = false;
	Planet* m_parent;
	
	

};

