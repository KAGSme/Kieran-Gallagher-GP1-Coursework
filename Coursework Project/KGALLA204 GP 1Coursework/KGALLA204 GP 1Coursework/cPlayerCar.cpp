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

void cPlayerCar::update(float deltaTime)
{

	if (m_InputMgr->isKeyDown(VK_RIGHT) && speedX <= maxSpeedX && spritePos2D.x < boundryX[1])
	{
		speedX += accelerationX * deltaTime;
		spriteRotation = 10.0f;
	}

	if (m_InputMgr->isKeyDown(VK_LEFT) && speedX >= -maxSpeedX && spritePos2D.x > boundryX[0])
	{
		speedX -= accelerationX * deltaTime;
		spriteRotation = -10.0f;
	}

	/*if (!m_InputMgr->wasKeyPressed(VK_RIGHT) && !m_InputMgr->wasKeyPressed(VK_LEFT))
	{
		spriteRotation = 0.0f;
	}*/

		spritePos2D.x += speedX;
}

void cPlayerCar::SetAccelerationX(float accelX)
{
	accelerationX = accelX;
}

void cPlayerCar::SetMaxSpeedX(float mSpeedX)
{
	maxSpeedX = mSpeedX;
}

void cPlayerCar::SetBoundriesX(int boundriesX1, int boundriesX2)
{
	boundryX[0] = boundriesX1;
	boundryX[1] = boundriesX2;
}