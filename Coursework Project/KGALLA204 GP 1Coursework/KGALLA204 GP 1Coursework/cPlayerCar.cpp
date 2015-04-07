/*
=================
cPlayerCar.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayerCar.h"
#include <sstream>

void cPlayerCar::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
		glColor3f(255.0f, 255.0f, 255.0f);

		glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
		glVertex2f(-(textureWidth / 2), -(textureHeight / 2));

		glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
		glVertex2f((textureWidth / 2), -(textureHeight / 2));

		glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
		glVertex2f((textureWidth / 2), (textureHeight / 2));

		glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
		glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

/*
===========================================
Update sprite position
===========================================
*/

void cPlayerCar::update(double deltaTime)
{
	ostringstream convert;
	
	convert << deltaTime;

	if (m_InputMgr->isKeyDown(VK_RIGHT) && spritePos2D.x < boundryX[1])
	{
		spritePos2D.x += speedX * deltaTime;
		spriteRotation = 10.0f;
		cout << "\n Right " + convert.str();
		
	}
	if (m_InputMgr->isKeyDown(VK_LEFT) && spritePos2D.x > boundryX[0])
	{
		spritePos2D.x -= speedX * deltaTime;
		spriteRotation = -10.0f;
		cout << "\n Left " + convert.str();
	}
	if (!m_InputMgr->isKeyDown(VK_LEFT) && !m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spriteRotation = 0.0f;
	}
}

void cPlayerCar::SetSpeedX(float velX)
{
	speedX = velX;
}

void cPlayerCar::SetBoundriesX(float boundriesX1, float boundriesX2)
{
	boundryX[0] = boundriesX1;
	boundryX[1] = boundriesX2;
}