/*************************************************************************
Copyright (c) 2012 Miroslav Andel
All rights reserved.

For conditions of distribution and use, see copyright notice in sgct.h 
*************************************************************************/

#ifndef _SGCT_VERTEX_DATA
#define _SGCT_VERTEX_DATA

namespace sgct_helpers
{

/*!
	This class stores a vertex which are used to generate vertex buffer objects (VBOs) in SGCT.
*/
class SGCTVertexData
{	
public:
	void set(float s, float t, float nx, float ny, float nz, float x, float y, float z)
	{
		mS = s;
		mT = t;
		mNx = nx;
		mNy = ny;
		mNz = nz;
		mX = x;
		mY = y;
		mZ = z;
	}
	
private:
	float mS, mT;	//Texcoord0 8
	float mNx, mNy, mNz; //12
	float mX, mY, mZ;	//12 = total 32 = power of two
	//ATI performs better using sizes of power of two
};
}

#endif
