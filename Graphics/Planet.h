#pragma once

#include "Application.h"
#include "Gizmos.h"



class Planet
{

public:
	Planet(bool hasRing,float speed, glm::vec3 position, float radius, int rows, int columns, glm::vec4 color, glm::mat4 transform);
	~Planet();
	void Draw();
	void Update(float deltaTime);
	void SetPosition(glm::vec3 position) { m_position = position; }
	void SetTime(float time) { m_time = time; }

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
	
	

};

