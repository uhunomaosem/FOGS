#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"

#define REFRESHRATE 16
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

private:

	float rotation;
	float rotation2;

	
};



