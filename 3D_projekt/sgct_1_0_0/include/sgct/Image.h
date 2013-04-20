/*************************************************************************
Copyright (c) 2012 Miroslav Andel
All rights reserved.

For conditions of distribution and use, see copyright notice in sgct.h 
*************************************************************************/

#ifndef _IMAGE_H_
#define _IMAGE_H_

namespace sgct_core
{

class Image
{
public:
	bool load(const char * filename);
	bool loadPNG(const char * filename);
	bool savePNG(const char * filename);
	void cleanup();
	unsigned char * getData();
	int getChannels();
	int getSizeX();
	int getSizeY();
	void setDataPtr(unsigned char * dPtr);
	void setSize(int width, int height);
	void setChannels(int channels);

private:
	int mChannels;
	int mSize_x;
	int mSize_y;
	char * mFilename;
	unsigned char * mData;
};

}

#endif

