// IFT3100H18_ShaderClassic/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

// énumération des types de shader
enum class ShaderType { color_fill, lambert, gouraud, phong, blinn_phong };

class Renderer
{
private:
	int rendererIter;
public:

	ShaderType shader_active;

	ofShader shader_color_fill;
	ofShader shader_lambert;
	ofShader shader_gouraud;
	ofShader shader_phong;
	ofShader shader_blinn_phong;

	ofShader* shader;

	ofLight light;

	ofVec3f position_cube;
	ofVec3f position_sphere;
	ofVec3f position_teapot;

	string shader_version;
	string shader_name;

	float oscillation;

	float scale_cube;
	float scale_sphere;
	float scale_teapot;

	float oscillation_frequency;
	float oscillation_amplitude;

	float speed_motion;

	float offset_x;
	float offset_z;

	float delta_x;
	float delta_z;

	float initial_x;
	float initial_y;

	float center_x;
	float center_y;

	int framebuffer_width;
	int framebuffer_height;

	int gl_version_major;
	int gl_version_minor;

	bool is_flip_axis_y;

	void setup();
	void update();
	void draw();
	void reset();

	void next();
};
