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

	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
	cSprite::spriteCentre = glm::vec2(0.0f, 0.0f);
	cSprite::setBoundingRect(&boundingRect);
}

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

GLuint cSprite::getTexture()  // Return the sprites current image
{
	return GLTextureID;
}

/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setTexture(GLuint GLtexID)  // set the image of the sprite
{
	GLTextureID = GLtexID;
}

/*
=================================================================================
  set the amount of movement on the x & y axis
=================================================================================
*/
void cSprite::setSpriteTranslation(glm::vec2 translation)
{
	spriteTranslation = translation;
}

/*
=================================================================================
  get the amount of movement on the x & y axis
=================================================================================
*/
glm::vec2 cSprite::getSpriteTranslation()
{
	return spriteTranslation;
}
/*
=================================================================================
  Set the sprites centre point
=================================================================================
*/
void cSprite::setSpriteCentre()
{
	spriteCentre.x = textureWidth / 2;
	spriteCentre.y = textureHeight / 2;
}

/*
=================================================================================
  return the sprites centre point
=================================================================================
*/
glm::vec2 cSprite::getSpriteCentre()
{
	return spriteCentre;
}
/*
=================
- set the rotation for the sprite.
=================
*/

void cSprite::setSpriteRotation(float angle)      // set the rotation for the sprite
{
	cSprite::spriteRotation = angle;
}
/*
=================
- return the rotation for the sprite.
=================
*/

float cSprite::getSpriteRotation()      // return the rotation for the sprite
{
	return cSprite::spriteRotation;
}
/*
=================
- Set the sprite to active.
=================
*/
void cSprite::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cSprite::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}


/*
=================================================================================
Default render function
=================================================================================
*/
void cSprite::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f,1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
		glColor3f(255.0f, 255.0f, 255.0f);
		glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
		glVertex2f(0, 0);
		glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
		glVertex2f( textureWidth, 0);
		glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
		glVertex2f(textureWidth, textureHeight);
		glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
		glVertex2f(0, textureHeight);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
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
void cSprite::setMdlRadius()
{
	m_Radius = textureWidth / 2;
}

float cSprite::getMdlRadius()
{
	return m_Radius;
}
/* 
=================================================================
   Attach the input manager to the sprite
=================================================================
*/
void cSprite::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}
/*
=================================================================
Attach the sound manager to the sprite
=================================================================
*/
void cSprite::attachSoundMgr(cSoundMgr* soundMgr)
{
	m_SoundMgr = soundMgr;
}
/*
=================
- Determine the bounding rectangle for the sprite.
=================
*/

void cSprite::setBoundingRect(RECT* pRect)
{
	glm::vec2 sPos = getSpritePos();
	RECT theBoundingRect;
	theBoundingRect.left = sPos.x;
	theBoundingRect.top = sPos.y;
	theBoundingRect.right = textureWidth + sPos.x;
	theBoundingRect.bottom = textureHeight + sPos.y;

	SetRect(pRect, (int)theBoundingRect.left, (int)theBoundingRect.top, (int)theBoundingRect.right, (int)theBoundingRect.bottom);
}
/*
=================
- Return the bounding rectangle for the sprite.
=================
*/
RECT cSprite::getBoundingRect()		// Return the bounding rectangle for the sprite
{
	return cSprite::boundingRect;
}
/*
=================
- Check for collisions.
=================
*/

bool cSprite::collidedWith(RECT thisSpriteRect, RECT otherSpriteRect)
{
	// declare rectangles for intersection test
	RECT tempRect;

	// perform the intersection test
	if (IntersectRect(&tempRect, &thisSpriteRect, &otherSpriteRect))
		return true;
	else
		return false;
}

bool cSprite::SphereSphereCollision(glm::vec2 spritePosition, float spriteRadius)
{
	const float distSq = lengthSQRD(spritePos2D - spritePosition);

	const float sumRadius = (m_Radius + spriteRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cSprite::lengthSQRD(glm::vec2 theLength)
{
	return (theLength.x * theLength.x) + (theLength.y * theLength.y);
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cSprite::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);
	
	glColor3f(255.0f, 0.0f, 0.0f);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(0, 0);
	//glVertex2f(0, boundingRect.bottom);
	//glVertex2f(boundingRect.right, boundingRect.bottom);
	//glVertex2f(boundingRect.right, 0);
	glBegin(GL_QUADS);
	glVertex2f(0 - textureWidth/2, 0 - textureHeight/2);
	glVertex2f(textureWidth - textureWidth / 2, 0 - textureHeight / 2);
	glVertex2f(textureWidth - textureWidth / 2, textureHeight - textureHeight / 2);
	glVertex2f(0 - textureWidth / 2, textureHeight - textureHeight/2);


	glEnd();

	glPopMatrix();
}
//returns texture dimensions
glm::vec2 cSprite::getTextureDimensions()
{
	return glm::vec2(textureWidth, textureHeight);
}
//generates a world matrix for sprite to be used in pixel collision
glm::mat4x4 cSprite::GetWorldMatrix()
{
	matrix = glm::mat4x4(1);
	matrix = glm::translate(matrix, glm::vec3(spritePos2D.x, spritePos2D.y, 0));
	matrix = glm::rotate(matrix, spriteRotation, glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(spriteScaling.x, spriteScaling.y, 1));
	return matrix;
}

/*
==========================================================================
Use this method to check for pixel collisions
==========================================================================
psuedo code can be found here http://gamedev.stackexchange.com/questions/23603/how-to-handle-pixel-perfect-collision-detection-with-rotation
*/

bool cSprite::PixelCollisionWith(cSprite* thisSprite, cSprite* otherSprite, cTexture* thisTex, cTexture* otherTex)
{
	glm::mat4x4 tMat = thisSprite->GetWorldMatrix();//generates Sprite world matrix
	glm::mat4x4 oMat = otherSprite->GetWorldMatrix();
	glm::mat4x4 oMatInverse = glm::inverse(oMat);//generates inverse of otherSprite world matrix

	glm::ivec2 tTextureSize = glm::ivec2(thisSprite->getTextureDimensions().x/2, thisSprite->getTextureDimensions().y/2);//dimensions must be halved for the centre of sprites in some cases(like player car)
	glm::ivec2 oTextureSize = glm::ivec2(otherSprite->getTextureDimensions().x/2, otherSprite->getTextureDimensions().y/2);
	for (int x = 0; x < thisSprite->getTextureDimensions().x; x++)
	{
		for (int y = 0; y < thisSprite->getTextureDimensions().y; y++)
		{
			bool solidThis = thisTex->GetPixelData(x, y) != 0;//checks if pixel is solid
			if (solidThis)
			{
				glm::vec4 pos = tMat * (glm::vec4(x, y, 0, 1) - glm::vec4(tTextureSize.x, tTextureSize.y, 0, 0));
				glm::vec4 positionOther = oMatInverse * pos + glm::vec4(oTextureSize.x, oTextureSize.y, 0, 0);

				if (positionOther.x < 0 || positionOther.y < 0 || 
					positionOther.x >= otherSprite->getTextureDimensions().x || positionOther.y >= otherSprite->getTextureDimensions().y)continue;//checks if pixel is 'out of bounds' with other sprite

				bool solidOther = otherTex->GetPixelData(positionOther.x, positionOther.y) != 0;//check if pixel is solid

				if (solidThis && solidOther) return true; // if both solid, COLLISION DETECTED!!!
			}
		}
	}
	return false;
}