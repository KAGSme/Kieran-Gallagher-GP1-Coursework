/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	cSprite::spritePos2D.x = 0;
	cSprite::spritePos2D.y = 0;
	cSprite::setSpriteTexCoordData();
}
/*
cSprite::cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename) // Constructor
{
	cSprite::setSpritePos(sPosition);
	cSprite::setTexture(pd3dDevice, theFilename);
}
*/
/*
=================
- Destructor 
=================
*/
cSprite::~cSprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

glm::vec2 cSprite::getSpritePos()  // Return the sprites current position
{
	return cSprite::spritePos2D;
}

/*
=================
- set the position of the sprite.
=================
*/

void cSprite::setSpritePos(glm::vec2 sPosition)  // set the position of the sprite
{
	cSprite::spritePos2D = sPosition;
}

/*
=================
- Return the sprites current image.
=================
*/
/*
LPDIRECT3DTEXTURE9 cSprite::getTexture()  // Return the sprites current image
{
	return cSprite::spriteTexture.getTexture();
}
*/
/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setTexture(GLuint GLtexID)  // set the image of the sprite
{
	GLTextureID = GLtexID;
}


void cSprite::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
		glColor3f(255.0f, 255.0f, 255.0f); //flush with white
		glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y); //providing uv mapping
		glVertex2f(spritePos2D.x, spritePos2D.y);
		glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
		glVertex2f(spritePos2D.x + textureWidth, spritePos2D.y);
		glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
		glVertex2f(spritePos2D.x + textureWidth, spritePos2D.y + textureHeight);
		glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
		glVertex2f(spritePos2D.x, spritePos2D.y + textureHeight);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void cSprite::setSpriteTexCoordData()
{
	spriteTexCoordData[0] = glm::vec2(0.0f, 0.0f);
	spriteTexCoordData[1] = glm::vec2(1.0f, 0.0f);
	spriteTexCoordData[2] = glm::vec2(1.0f, 1.0f);
	spriteTexCoordData[3] = glm::vec2(0.0f, 1.0f);
}

void cSprite::setTextureDimensions(int texWidth, int textHeight)
{
	textureWidth = texWidth;
	textureHeight = textHeight;
}
