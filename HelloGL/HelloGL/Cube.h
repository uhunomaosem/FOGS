#pragma once
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	//static Vertex* indexedVertices;
	//static Colour* indexedColours;
	//static GLushort* indices;
	
	GLfloat _rotation;
	//Camera* camera;
	Vector3 _position;
	static int numVertices, numColours, numIndices;


public:
	Cube(Mesh* mesh,Texture2D* texture, float x, float y, float z);
	~Cube();
	static bool Load(char* path);
	void Draw();
	void Update();
};
