#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "Planet.h"
#include <list>


class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();
	void Planets();

	virtual void update(float deltaTime);
	virtual void draw();


protected:
	bool LaunchShaders();
	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	
	aie::ShaderProgram	m_simpleShader;
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	std::list<Planet*> m_planets;
 	
	Planet* m_sun;
	Planet* m_mercury;
	Planet* m_venus;
	Planet* m_earth;
	Planet* m_mars;
	Planet* m_jupiter;
	Planet* m_saturn;
	Planet* m_uranus;
	Planet* m_neptune;

};