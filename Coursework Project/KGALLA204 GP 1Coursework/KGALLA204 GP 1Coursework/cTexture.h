/*
=================
cTexture.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DXTexture class
=================
*/
#ifndef _CTEXTURE_H
#define _CTEXTURE_H
#include "GameConstants.h"

class cTexture
{
private:
	GLuint GLTextureID;
	GLuint aTextureInfo;
	GLsizei textureWidth;
	GLsizei textureHeight;
	int pitch;
	ILuint ilTextureID;
	char *txData;

public:
	cTexture();
	cTexture(LPCSTR theFilename);
	~cTexture();
	bool createTexture(LPCSTR theFilename);		// create the texture for use.
	GLuint getTexture();						// return the texture.
	GLsizei getTWidth();						// Return width of texture;
	GLsizei getTHeight();						// Return height of texture;
	int GetPixelData(int x, int y);
};
#endif