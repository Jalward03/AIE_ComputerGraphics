#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <math.h>
#include <imgui.h>

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

	m_viewMatrix =
		glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	// create simple camera transforms
	m_projectionMatrix =
		glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);


	m_ambientLight = { 0.5,0.5,0.5 };

	Light light;
	light.color = { 1,1,1 };
	light.direction = { 1,-1,1 };


	m_scene = new Scene(&m_camera, glm::vec2(getWindowWidth(), getWindowHeight()),
		light, m_ambientLight);

	m_bunnyEnabled = false;
	m_planetsEnabled = false;
	m_boxEnabled = false;
	m_quadEnabled = false;
	m_pyramidEnabled = false;
	m_discEnabled = false;
	m_cylinderEnabled = false;
	m_coneEnabled = false;
	m_quadTexturedEnabled = false;
	m_spearEnabled = false;
	m_batarangEnabled = false;

	Planets();
	return LaunchShaders();

	return true;
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
	delete m_scene;
}

void GraphicsApp::Planets()
{

	m_planets.push_back(m_sun = new Planet(false, false, 0, vec3(0, 0, 0), 1.5, 12, 12, vec4(1, 1, 0, 1)));
	m_planets.push_back(m_mercury = new Planet(false, false, 2, vec3(2, 0, 2), 0.15, 24, 24, vec4(1, 1, 0, 0.5f)));
	m_planets.push_back(m_venus = new Planet(false, false, 1.5, vec3(3, 0, 3), 0.25, 24, 24, vec4(1, 0.647, 0, 1)));
	m_planets.push_back(m_earth = new Planet(false, false, 1.25, vec3(4, 0, 4), 0.3, 24, 24, vec4(0, 0, 1, 1)));
	m_planets.push_back(m_mars = new Planet(false, false, 1, vec3(6, 0, 6), 0.2, 24, 24, vec4(1, 0, 0, 1)));
	m_planets.push_back(m_jupiter = new Planet(false, false, 0.75, vec3(7.25, 0, 7.25), 0.7, 24, 24, vec4(1, 0.647, 0, 0.5f)));
	m_planets.push_back(m_saturn = new Planet(true, false, 0.5, vec3(8, 0, 8), 0.6, 24, 24, vec4(1, 1, 0.7, 1)));
	m_planets.push_back(m_uranus = new Planet(true, false, 0.25, vec3(9, 0, 9), 0.5, 24, 24, vec4(0.678, 0.847, 0.902, 1)));
	m_planets.push_back(m_neptune = new Planet(false, false, 0.15, vec3(10, 0, 10), 0.45, 24, 24, vec4(0, 0, 1, 0.75)));
	//m_moon->SetParent(m_earth);
	//m_planets.push_back(m_moon = new Planet(false, true, 3, vec3(5, 0, 0), 1, 12, 12, vec4(1, 1, 1, 1)));

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

	float time = getTime();

	// Rotate the light to emulate a 'day/night' cycle
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	m_camera.Update(deltaTime);


	for (auto planet : m_planets)
	{
		planet->SetTime(time);
		planet->Update(deltaTime);
	}


	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	ImGUIRefresher();

	m_boxTransform = glm::rotate(m_boxTransform, 0.05f, glm::vec3(0, 1, 1));
	m_pyramidTransform = glm::rotate(m_pyramidTransform, 0.05f, glm::vec3(0, 1, 1));
	m_discTransform = glm::rotate(m_discTransform, 0.05f, glm::vec3(0, 1, 1));
	m_coneTransform = glm::rotate(m_coneTransform, 0.05f, glm::vec3(0, 1, 1));


}

void GraphicsApp::draw() {


	// wipe the screen to the background colour
	clearScreen();



	// update perspective based on screen size
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	m_viewMatrix = m_camera.GetViewMatrix();
	m_projectionMatrix = m_camera.GetProjectionMatrix(getWindowWidth(),
		getWindowHeight());
	auto pv = m_projectionMatrix * m_viewMatrix;

	m_scene->Draw();


	if (m_planetsEnabled)
	{
		for (auto planet : m_planets)
		{
			planet->Draw();
		}
	}
	if (m_bunnyEnabled)ObjDraw(pv, m_bunnyTransform, &m_bunnyMesh);

	if (m_boxEnabled) BoxDraw(pv * m_boxTransform);
	if (m_quadEnabled) QuadDraw(pv * m_quadTransform);
	if (m_quadTexturedEnabled) QuadTextureDraw(pv * m_quadTransform);
	if (m_pyramidEnabled) PyramidDraw(pv * m_pyramidTransform);
	if (m_discEnabled) DiscDraw(pv * m_discTransform);
	if (m_coneEnabled) ConeDraw(pv * m_coneTransform);
	//if (m_cylinderEnabled) CylinderDraw(pv * m_cylinderTransform);
	if (m_spearEnabled) ObjDraw(pv, m_spearTransform, &m_spearMesh);
	if (m_batarangEnabled) ObjDraw(pv, m_batarangTransform, &m_batarangMesh);




	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

bool GraphicsApp::LaunchShaders()
{
	m_normalLitShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/normalLit.vert");
	m_normalLitShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/normalLit.frag");

	if (m_normalLitShader.link() == false)
	{
		printf("Normal Lit Phong shader Error : %s\n", m_normalLitShader.getLastError());
		return false;
	}

	if (!QuadLoader())
		return false;


	if (!BunnyLoader())
		return false;

	if (!BoxLoader())
		return false;

	if (!PyramidLoader())
		return false;


	if (!DiscLoader())
		return false;


	if (!ConeLoader())
		return false;

	//if (!CylinderLoader())
	//	return false;


	if (!QuadTextureLoader())
		return false;


	if (!SpearLoader())
		return false;

	if (!BatarangLoader())
		return false;






	m_scene->AddInstance(new Instance(m_spearTransform,
		&m_spearMesh, &m_normalLitShader));

	return true;
}

void GraphicsApp::ImGUIRefresher()
{
	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Global Light Direction", &m_light.direction[0], 0.1, -1, 1);
	ImGui::DragFloat3("Global Light Color", &m_light.color[0], 0.1, 0, 1);
	ImGui::End();

	ImGui::Begin("Objects");
	ImGui::Checkbox("Planets", &m_planetsEnabled);
	ImGui::Checkbox("Bunny", &m_bunnyEnabled);
	ImGui::Checkbox("Spear", &m_spearEnabled);
	ImGui::Checkbox("Batarang", &m_batarangEnabled);
	ImGui::End();

	ImGui::Begin("Shapes");
	ImGui::Checkbox("Quad", &m_quadEnabled);
	ImGui::Checkbox("Textured Quad", &m_quadTexturedEnabled);
	ImGui::Checkbox("Box", &m_boxEnabled);
	ImGui::Checkbox("Pyramid", &m_pyramidEnabled);
	ImGui::Checkbox("Disc", &m_discEnabled);
	ImGui::Checkbox("Cone", &m_coneEnabled);
	ImGui::Checkbox("Cylinder", &m_cylinderEnabled);
	ImGui::End();


}

bool GraphicsApp::PyramidLoader()
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


	Mesh::Vertex vertices[5];

	// Bottom face
	vertices[0].position = { -0.5f, 0,  0.5f, 1 };
	vertices[1].position = { 0.5f, 0,  0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	// Top point
	vertices[4].position = { 0, 1, 0, 1 };



	unsigned int indices[18] =
	{
		0,2,1, // bottom
		2,3,1,
		4,2,0, // Faces
		4,3,2,
		4,1,3,
		4,0,1


	};

	m_pyramidMesh.Initialise(5, vertices, 18, indices);

	//m_quadMesh.InitialiseQuad();
	m_pyramidTransform = {
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1
	};
}

void GraphicsApp::PyramidDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color

	m_pyramidMesh.Draw();
}

bool GraphicsApp::QuadLoader()
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

	// Defined as 4 vertices for the 2 triangles

	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0,  0.5f, 1 };
	vertices[1].position = { 0.5f, 0,  0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };

	unsigned int indices[6] = { 0,1,2,2,1,3 };

	//m_quadMesh.Initialise(4, vertices, 6, indices);

	//m_quadMesh.InitialiseQuad();
	// This is a 10 'unit' wide quad
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};
}

void GraphicsApp::QuadDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color

	m_quadMesh.Draw();
}

bool GraphicsApp::ConeLoader()
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

	// Defined as 4 vertices for the 2 triangles

	Mesh::Vertex vertices[17];
	vertices[0].position = { 0, 2,  0, 1 }; // Center

	for (int i = 1; i < 17; i++)
	{
		vertices[i].position = { glm::sin(i * 0.45f), 0, glm::cos(i * 0.45f), 1 };
	}

	unsigned int indices[48];

	for (int i = 0; i < 48; i += 3)
	{
		indices[i] = 0;
		indices[i + 1] = i / 3;
		indices[i + 2] = i / 3 + 1;


	}

	m_coneMesh.Initialise(17, vertices, 48, indices);

	//m_quadMesh.InitialiseQuad();
	// This is a 10 'unit' wide quad
	m_coneTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

void GraphicsApp::ConeDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color

	m_coneMesh.Draw();
}

bool GraphicsApp::DiscLoader()
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

	// Defined as 4 vertices for the 2 triangles

	Mesh::Vertex vertices[17];
	vertices[0].position = { 0, 0,  0, 1 }; // Center

	for (int i = 1; i < 17; i++)
	{
		vertices[i].position = { glm::sin(i * 0.45f), 0, glm::cos(i * 0.45f), 1 };
	}

	unsigned int indices[48];

	for (int i = 0; i < 48; i += 3)
	{
		indices[i] = 0;
		indices[i + 1] = i / 3;
		indices[i + 2] = i / 3 + 1;


	}

	m_discMesh.Initialise(17, vertices, 48, indices);

	//m_quadMesh.InitialiseQuad();
	// This is a 10 'unit' wide quad
	m_discTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

void GraphicsApp::DiscDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color

	m_discMesh.Draw();
}


bool GraphicsApp::BoxLoader()
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

	// Defined as 4 vertices for the 2 triangles

	Mesh::Vertex vertices[8];

	// Bottom face
	vertices[0].position = { -0.5f, 0,  0.5f, 1 };
	vertices[1].position = { 0.5f, 0,  0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	vertices[4].position = { -0.5f, 1,  0.5f, 1 };
	vertices[5].position = { 0.5f, 1,  0.5f, 1 };
	vertices[6].position = { -0.5f, 1, -0.5f, 1 };
	vertices[7].position = { 0.5f, 1, -0.5f, 1 };



	unsigned int indices[36] =
	{
		0,2,1, // bottom
		2,3,1,
		4,5,6, // top
		6,5,7,
		1,5,0, // backleft
		5,4,0,
		3,7,1, // Front Left
		5,1,7,
		2,7,3, // Front Right
		6,7,2,
		2,0,4, // Front Left
		6,2,4


	};

	m_boxMesh.Initialise(8, vertices, 36, indices);

	//m_quadMesh.InitialiseQuad();
	m_boxTransform = {
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1
	};
}

void GraphicsApp::BoxDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color

	m_boxMesh.Draw();
}

bool GraphicsApp::BunnyLoader()
{
	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("Color shader Error : %s\n", m_phongShader.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Error!");
		return false;
	}

	m_bunnyTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 2
	};

	return true;
}

void GraphicsApp::BunnyDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_phongShader.bind();

	// Bind the transform

	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color
	m_phongShader.bindUniform("BaseColor", glm::vec4(1));


	m_bunnyMesh.draw();
}

bool GraphicsApp::SpearLoader()
{

	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!");
		return false;
	}

	m_spearTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 2
	};

	return true;
}

void GraphicsApp::ObjDraw(glm::mat4 pv, glm::mat4 transform, aie::OBJMesh* objMesh)
{
	m_normalLitShader.bind();

	// Bind the camera position
	m_normalLitShader.bindUniform("CameraPosition",
		glm::vec3(glm::inverse(m_viewMatrix)[3]));

	m_normalLitShader.bindUniform("LightDirection", m_light.direction);
	m_normalLitShader.bindUniform("LightColor", m_light.color);
	m_normalLitShader.bindUniform("AmbientColor", m_ambientLight);

	m_normalLitShader.bindUniform("diffuseTexture", 0);
	m_normalLitShader.bindUniform("ProjectionViewModel", pv * transform);

	m_normalLitShader.bindUniform("ModelMatrix", transform);

	objMesh->draw();

}

bool GraphicsApp::BatarangLoader()
{


	if (m_batarangMesh.load("./batarang/Batarang_SketchFab.obj", true, true) == false)
	{
		printf("Bataraang Mesh Error!");
		return false;
	}

	m_batarangTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 0.5f
	};

	m_batarangTransform = glm::rotate(m_batarangTransform, glm::radians(90.f), glm::vec3(0, 90, 0));

	return true;
}



void GraphicsApp::BatarangDraw(glm::mat4 pvm)
{
	m_colorShader.bind();

	m_colorShader.bindUniform("ProjectionViewModel", pvm);

	m_colorShader.bindUniform("BaseColor", glm::vec4(1));

	m_batarangMesh.draw();

}

bool GraphicsApp::QuadTextureLoader()
{
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/textured.frag");


	if (m_texturedShader.link() == false)
	{
		printf("Textured Shader has an Error: %s\n",
			m_texturedShader.getLastError());
		return false;
	}

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load the grid texture correctly!\n");
		return false;
	}

	// Defined as 4 vertices for the 2 triangles


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

void GraphicsApp::QuadTextureDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_texturedShader.bind();

	// Bind the transform

	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the texture location
	m_texturedShader.bindUniform("diffuseTexture", 0);

	// Bind the texture to a specific location
	m_gridTexture.bind(0);

	// Bind the color

	m_quadMesh.Draw();
}

void GraphicsApp::PhongDraw(glm::mat4 pvm, glm::mat4 transform)
{
	// Bind the phong shader
	m_phongShader.bind();

	// Bind the camera position
	m_phongShader.bindUniform("CameraPosition",
		glm::vec3(glm::inverse(m_viewMatrix)[3]));

	m_phongShader.bindUniform("LightDirection", m_light.direction);
	m_phongShader.bindUniform("LightColor", m_light.color);
	m_phongShader.bindUniform("AmbientColor", m_ambientLight);

	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	m_phongShader.bindUniform("ModelMatrix", transform);

	m_bunnyMesh.draw();


}
