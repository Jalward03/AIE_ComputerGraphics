#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "Planet.h"
#include "OBJMesh.h"
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
	void ImGUIRefresher();
	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);
	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	
	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;


	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;
	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	struct Light {
		glm::vec3 direction;
		glm::vec3 color;
	};
	Light m_light;
	glm::vec3 m_ambientLight;

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
	Planet* m_moon;

};