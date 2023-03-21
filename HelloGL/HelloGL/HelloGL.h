#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Texture2D.h"

#define REFRESHRATE 16
#define CUBES 200



class HelloGL
{
public:

	//contructor definition
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	//make sure the application window is present
	void Display();

	//handles drawing of shape
	void DrawPolygon();

	void Update();

	//Handles keyboard input
	void KeyBoard(unsigned char key, int x, int y);

	////draw indexed cube
	//void DrawIndexedCube();

	////to draw cube
	//void DrawCubeArray();


	void InitObjects();
	void InitGL(int argc, char* argv[]);


private:

	//float rotation;
	//float rotation2;
	//Camera* camera;
	//static Vertex vertices[];
	//static Colour colours[];
	//static Vertex indexedVertices[];
	//static Colour indexedColours[];
	//static GLushort indices[];
	Camera* camera;
	SceneObject* objects[1000];
	//Cube* Update;
};



