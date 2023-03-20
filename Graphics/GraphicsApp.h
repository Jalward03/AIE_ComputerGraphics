#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "Planet.h"
#include "OBJMesh.h"
#include <list>
#include "SimpleCamera.h"


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

	bool PyramidLoader();
	void PyramidDraw(glm::mat4 pvm);

	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool CylinderLoader();
	void CylinderDraw(glm::mat4 pvm);


	bool BoxLoader();
	void BoxDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	bool QuadTextureLoader();
	void QuadTextureDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);
	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;
	
	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;
	aie::ShaderProgram m_texturedShader;


	Mesh				m_quadMesh;
	Mesh				m_boxMesh;
	Mesh				m_pyramidMesh;
	Mesh				m_cylinderMesh;

	glm::mat4			m_quadTransform;
	glm::mat4           m_boxTransform;
	glm::mat4           m_pyramidTransform;
	glm::mat4           m_cylinderTransform;

	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	SimpleCamera m_camera;

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

	bool m_bunnyEnabled;
	bool m_planetsEnabled;


	bool m_boxEnabled;
	bool m_quadEnabled;
	bool m_quadTexturedEnabled;
	bool m_pyramidEnabled;
	bool m_cylinderEnabled;

};