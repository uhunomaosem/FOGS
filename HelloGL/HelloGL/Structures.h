#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat	x, y, z;
};

struct Mesh
{
	Vertex* Vertices;
	Colour* Colours;
	GLushort* Indices;
	int VertexCount, ColourCount, IndexCount;
};
