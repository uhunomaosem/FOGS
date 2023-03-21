#include "Cube.h"
#include <fstream>
#include <iostream>
#include <string>
#include <istream>




//Vertex Cube::indexedVertices[] = {/* 1, 1, 1,  -1, 1, 1,  */// v0,v1,
//				/*-1,-1, 1,   1,-1, 1,*/   // v2,v3
//				/*1,-1,-1,   1, 1,-1,  */  // v4,v5
//				/*-1, 1,-1,   -1,-1,-1*/ }; // v6,v7
//
//Colour Cube::indexedColours[] = { /*1, 1, 1,   1, 1, 0,*/   // v0,v1,
//				/*1, 0, 0,   1, 0, 1,*/   // v2,v3
//				/*0, 0, 1,   0, 1, 1, */  // v4,v5
//				/*0, 1, 0,   0, 0, 0*/ }; //v6,v7
//
//GLushort Cube::indices[] = { /*0, 1, 2,  2, 3, 0,  */    // front
//				/*0, 3, 4,  4, 5, 0,*/      // right
//				/*0, 5, 6,  6, 1, 0, */     // top
//				/*1, 6, 7,  7, 2, 1, */     // left
//				/*7, 4, 3,  3, 2, 7,  */    // bottom
//				/*4, 7, 6,  6, 5, 4*/ };    // back

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;


Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh,texture)
{

	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if (_mesh->Vertices != nullptr && _mesh->Colours != nullptr && _mesh->Indices != nullptr)
	{
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TextCoords);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 36; i++)
		{
			//Implement draw code here

			glColor3f(_mesh->Colours[_mesh->Indices[i]].r, _mesh->Colours[_mesh->Indices[i]].g, _mesh->Colours[_mesh->Indices[i]].b);
			glVertex3f(_mesh->Vertices[_mesh->Indices[i]].x, _mesh->Vertices[_mesh->Indices[i]].y, _mesh->Vertices[_mesh->Indices[i]].z);
		}
		glEnd();

		glPopMatrix();

	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void Cube::Update()
{
	glLoadIdentity();
	//gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
	_rotation += 0.95f;

	if (_rotation > 360.0)
	{
		_rotation = 0.0f;
	}
}


//bool Cube::Load(char* path)
//{
//	std::ifstream inFile;
//	inFile.open(path);
//	if (!inFile.good())
//	{
//		std::cerr << "Can't open text file " << path << std::endl;
//		return false;
//	}
//
//	inFile >> numVertices;
//	indexedVertices = new Vertex[numVertices];
//	for (int i = 0; i < numVertices; i++)
//	{
//		//TODO Use inFile to populate the indexedVertices array
//		inFile >> indexedVertices[i].x;
//		inFile >> indexedVertices[i].y;
//		inFile >> indexedVertices[i].z;
//	}
//
//	//TODO: Load Color information
//	inFile >> numColours;
//	indexedColours = new Colour[numColours];
//	for (int i = 0; i < numColours; i++)
//	{
//		inFile >> indexedColours[i].r;
//		inFile >> indexedColours[i].g;
//		inFile >> indexedColours[i].b;
//	}
//
//	//TODO: Load Indices information
//	inFile >> numIndices;
//	indices = new GLushort[numIndices];
//	for (int i = 0; i < numIndices; i++)
//	{
//		inFile >> indices[i];
//	}
//
//	inFile.close();
//
//	return true;
//}
