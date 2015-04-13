/*
=================
cEnemyCar.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemyCar.h"

void cEnemyCar::SetSpeedY(float velY)
{
	speedY = velY;
}
//checks to see if the car has left the bottom of the screen------------------------
bool cEnemyCar::IsOffScreen_Bottom() 
{
	if (spritePos2D.y > 700) return true;
	else return false;
}
//Render function (set up to makes sure the sprite is also centered)----------------------------
void cEnemyCar::render()
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
// cEnemyCar;s update function-------------------------------------------
void cEnemyCar::update(double deltaTime)
{
	
	spritePos2D.y += speedY * deltaTime;//moves car downwards

	setBoundingRect(&boundingRect);
}