#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "Planet.h"
#include "OBJMesh.h"
#include <list>
#include "FlyCamera.h"
#include "StationaryCamera.h"
#include "Scene.h"
#include"Instance.h"
#include "CameraBase.h"
#include "ParticleEmitter.h"


#include "RenderTarget.h"


class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();
	
	virtual bool startup();
	virtual void shutdown();
	void Planets();

	virtual void update(float deltaTime);
	virtual void draw();
	void CamDraw(CameraBase* cam);
	void DisableCams();

	
protected:
	bool LaunchShaders();
	void ImGUIRefresher();

	bool PyramidLoader();
	void PyramidDraw(glm::mat4 pvm);

	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool ConeLoader();
	void ConeDraw(glm::mat4 pvm);
	
	//bool CylinderLoader();
	//void CylinderDraw(glm::mat4 pvm);

	bool DiscLoader();
	void DiscDraw(glm::mat4 pvm);


	bool BoxLoader();
	void BoxDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	bool SpearLoader();
	void ObjDraw(glm::mat4 pv, glm::mat4 transform, aie::OBJMesh* objMesh);

	bool BatarangLoader();
	void BatarangDraw(glm::mat4 pvm);

	bool QuadTextureLoader();
	void QuadTextureDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

	int m_postProcessEffect = -1;

	Scene*		m_scene;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;
	
	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;
	aie::ShaderProgram m_texturedShader;
	aie::ShaderProgram m_normalLitShader;
	aie::ShaderProgram m_postProcessShader;
	aie::ShaderProgram m_particleShader;

	aie::RenderTarget m_renderTarget;


	Mesh				m_quadMesh;
	Mesh				m_boxMesh;
	Mesh				m_pyramidMesh;
	Mesh				m_discMesh;
	Mesh				m_coneMesh;
	Mesh				m_cylinderMesh;
	Mesh				m_fullScreenQuad;

	glm::mat4			m_quadTransform;
	glm::mat4           m_boxTransform;
	glm::mat4           m_pyramidTransform;
	glm::mat4           m_discTransform;
	glm::mat4           m_coneTransform;
	glm::mat4           m_cylinderTransform;

	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	aie::OBJMesh		m_batarangMesh;
	glm::mat4			m_batarangTransform;

	CameraBase* m_baseCamera;
	FlyCamera m_flyCamera;
	StationaryCamera m_stationaryCameraX;
	StationaryCamera m_stationaryCameraY;
	StationaryCamera m_stationaryCameraZ;
	//CameraBase m_cameras = m_camera;

	//struct Light {
	//	glm::vec3 direction;
	//	glm::vec3 color;
	//};
	Light m_light;
	glm::vec3 m_ambientLight;

	ParticleEmitter* m_emitter;
	glm::mat4 m_particleEmitTransform;

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
	bool m_discEnabled;
	bool m_coneEnabled;
	bool m_cylinderEnabled;
	bool m_spearEnabled;
	bool m_batarangEnabled;


	bool m_flyCameraEnabled;
	bool m_stationaryCameraXEnabled;
	bool m_stationaryCameraYEnabled;
	bool m_stationaryCameraZEnabled;
	bool m_orbitCameraEnabled;
	

};