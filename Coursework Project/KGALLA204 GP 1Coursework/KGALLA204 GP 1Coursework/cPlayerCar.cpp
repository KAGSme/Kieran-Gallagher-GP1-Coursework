/*
=================
cPlayerCar.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayerCar.h"

void cPlayerCar::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

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

	glPopMatrix();
}

/*
===========================================
Update sprite position
===========================================
*/

void cPlayerCar::update(float deltaTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spriteRotation = 10.0f;
		spritePos2D.x += speedX;
	}

	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spriteRotation = -10.0f;
		spriteCentre.x -= speedX;
	}
}

void cPlayerCar::attachInputMgr(cInputMgr* InputMgr)
{
	m_InputMgr = InputMgr;
}