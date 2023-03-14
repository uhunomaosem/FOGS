#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex* indexedVertices;
	static Colour* indexedColours;
	static GLushort* indices;
	GLfloat _rotation;
	//Camera* camera;
	Vector3 _position;
	static int numVertices, numColours, numIndices;


public:
	Cube(float x, float y, float z);
	~Cube();
	static bool Load(char* path);
	void Draw();
	void Update();
};
