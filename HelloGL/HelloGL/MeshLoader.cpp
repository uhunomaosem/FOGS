#include "MeshLoader.h"


#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		//TODO: LOAD COLOURS
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load Indices
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE

		
		inFile >> mesh->VertexCount;
		mesh->Vertices = new Vertex[mesh->VertexCount];
		for (int i = 0; i < mesh->VertexCount; i++)
		{
			//TODO Use inFile to populate the indexedVertices array
			inFile >> mesh->Vertices[i].x;
			inFile >> mesh->Vertices[i].y;
			inFile >> mesh->Vertices[i].z;
		}

		//TODO: Load Color information
		inFile >> mesh->ColourCount;
		mesh->Colours = new Colour[mesh->ColourCount];
		for (int i = 0; i < mesh->ColourCount; i++)
		{
			inFile >> mesh->Colours[i].r;
			inFile >> mesh->Colours[i].g;
			inFile >> mesh->Colours[i].b;
		}

		//TODO: Load Indices information
		inFile >> mesh->IndexCount;
		mesh->Indices = new GLushort[mesh->IndexCount];
		for (int i = 0; i < mesh->IndexCount; i++)
		{
			inFile >> mesh->Indices[i];
		}

		inFile.close();

		return mesh;

	}

}