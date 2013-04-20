/*************************************************************************
Copyright (c) 2012 Miroslav Andel
All rights reserved.

For conditions of distribution and use, see copyright notice in sgct.h 
*************************************************************************/

#ifndef _CORRECTION_MESH_H_
#define _CORRECTION_MESH_H_

struct CorrectionMeshVertex
{
	float x, y;	//Vertex 8
	float s0, t0;	//Texcoord0 8
	float s1, t1;	//Texcoord1 8
	unsigned char r, g, b; //color 3

	//ATI performs better using sizes of power of two
	unsigned char padding[5]; //32 - 8 - 8 - 8 - 3 = 5
};

namespace sgct_core
{

/*!
Helper class for reading and rendering a correction mesh.
A correction mesh is used for warping and edge-blending.
*/
class CorrectionMesh
{
public:
	CorrectionMesh();
	~CorrectionMesh();
	void setViewportCoords(float vpXSize, float vpYSize, float vpXPos, float vpYPos);
	bool readAndGenerateMesh(const char * meshPath);
	void render();
	inline const double * getOrthoCoords() { return &mOrthoCoords[0]; }

private:
	void createMesh();
	void cleanUp();
	void renderMesh();

	enum buffer { Vertex = 0, Index };

	CorrectionMeshVertex * mVertices;
	CorrectionMeshVertex * mVertexList;
	unsigned int * mFaces;
    double mOrthoCoords[5];
	unsigned int mResolution[2];

	unsigned int mNumberOfVertices;
	unsigned int mNumberOfFaces;
	unsigned int mMeshData[2];

	float mXSize;
	float mYSize;
	float mXOffset;
	float mYOffset;
	
	bool hasMesh;
};

} //sgct_core

#endif
