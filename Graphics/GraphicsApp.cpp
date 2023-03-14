#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsApp::GraphicsApp() 
{
}

GraphicsApp::~GraphicsApp() {

}

bool GraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	Planets();
	return LaunchShaders();
	return true;
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsApp::Planets()
{

	//m_planets.push_back(m_sun = new Planet(false, 0, vec3(0, 0, 0), 1.5, 24, 24, vec4(1, 1, 0, 1)));
	//m_planets.push_back(m_mercury = new Planet(false, 2, vec3(3, 0, 3), 0.15, 24, 24, vec4(1, 1, 0, 0.5f)));
	//m_planets.push_back(m_venus = new Planet(false, 1.5, vec3(4, 0, 4), 0.25, 24, 24, vec4(1, 0.647, 0, 1)));
	//m_planets.push_back(m_earth = new Planet(false, 1.25, vec3(5, 0, 5), 0.3, 24, 24, vec4(0, 0, 1, 1)));
	//m_planets.push_back(m_mars = new Planet(false, 1, vec3(7, 0, 7), 0.2, 24, 24, vec4(1, 0, 0, 1)));
	//m_planets.push_back(m_jupiter = new Planet(false, 0.75, vec3(8.25, 0, 8.25), 0.7, 24, 24, vec4(1, 0.647, 0, 0.5f)));
	//m_planets.push_back(m_saturn = new Planet(true, 0.5, vec3(10, 0, 10), 0.6, 24, 24, vec4(1, 1, 0.7, 1)));
	//m_planets.push_back(m_uranus = new Planet(false, 0.25, vec3(12, 0, 12), 0.5, 24, 24, vec4(0.678, 0.847, 0.902, 1)));
	//m_planets.push_back(m_neptune = new Planet(false, 0.1, vec3(13, 0, 13), 0.45, 24, 24, vec4(0, 0, 1, 0.75)));
	//m_mercury = new Planet()
}

void GraphicsApp::update(float deltaTime) {

	
	
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


	
	float time = Application::getTime();
	for (auto planet : m_planets)
	{
		planet->SetTime(time);
		planet->Update(deltaTime);
	}
}

void GraphicsApp::draw() {

	
	// wipe the screen to the background colour
	clearScreen();
	for (auto planet : m_planets)
	{
		planet->Draw();
	}


	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

#pragma region SimpleShader
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the quad using Mesh's draw
	m_quadMesh.Draw();

#pragma endregion


	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

bool GraphicsApp::LaunchShaders()
{
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");


	if (!m_simpleShader.link())
	{
		printf("Simple Shader has an Error: %\n", 
			m_simpleShader.getLastError());
		return false;
	}

	m_quadMesh.InitialiseQuad();
	// This is a 10 'unit' wide quad
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};

	return true;
}
