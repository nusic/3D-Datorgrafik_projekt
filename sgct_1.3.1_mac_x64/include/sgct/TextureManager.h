/*************************************************************************
Copyright (c) 2012 Miroslav Andel
All rights reserved.

For conditions of distribution and use, see copyright notice in sgct.h 
*************************************************************************/

#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <vector>
#include <string>

namespace sgct //simple graphics cluster toolkit
{

/*!
	The TextureManager loads and handles textures. It is a singleton and can be accessed anywhere using its static instance. Currently only PNG textures are supported.
*/
class TextureManager
{
public:
	/*!
		The compression mode modes. For more info about texute compression look here: <a href="http://en.wikipedia.org/wiki/S3_Texture_Compression">S3 Texture compression</a>
	*/
	enum CompressionMode { No_Compression = 0, Generic, S3TC_DXT };

	/*! Get the TextureManager instance */
	static TextureManager * Instance()
	{
		if( mInstance == NULL )
		{
			mInstance = new TextureManager();
		}

		return mInstance;
	}

	/*! Destroy the TextureManager */
	static void Destroy()
	{
		if( mInstance != NULL )
		{
			delete mInstance;
			mInstance = NULL;
		}
	}

	const unsigned int getTextureByHandle(const std::size_t handle);
	const unsigned int getTextureByName(const std::string name);

	void setAnisotropicFilterSize(float fval);
	void setAlphaModeForSingleChannelTextures(bool alpha) {mAlphaMode = alpha;}
	void setCompression(CompressionMode cm);
	void setWarpingMode(int warp_s, int warp_t);
	bool loadTexure(std::size_t &handle, const std::string name, const std::string filename, bool interpolate, int mipmapLevels = 8);
	bool loadTexure(const std::string name, const std::string filename, bool interpolate, int mipmapLevels = 8);

private:
	TextureManager();
	~TextureManager();

	void freeTextureData();

	// Don't implement these, should give compile warning if used
	TextureManager( const TextureManager & tm );
	const TextureManager & operator=(const TextureManager & rhs );

private:
	bool getIndexByName(std::size_t &handle, const std::string name);

	static TextureManager * mInstance;
	
	float mAnisotropicFilterSize;
	CompressionMode mCompression;
	bool mAlphaMode;
	std::vector< std::pair<std::string, unsigned int> > mTextures;
	int mWarpMode[2];
};

}

#endif
