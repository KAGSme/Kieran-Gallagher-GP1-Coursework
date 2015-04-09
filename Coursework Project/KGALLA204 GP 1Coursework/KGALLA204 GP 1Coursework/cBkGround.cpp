/*
=================
cBkGround.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBkGround.h"

void cBkGround::render()
{ 
	cSprite::render();
}
/*
=================================================================
Update the sprite position
=================================================================
*/
float scrollSpeed = 1.5;
void cBkGround::update(double deltaTime)
{
	spriteTexCoordData[0] -= glm::vec2(0, scrollSpeed * deltaTime);
	spriteTexCoordData[1] -= glm::vec2(0, scrollSpeed * deltaTime);
	spriteTexCoordData[2] -= glm::vec2(0, scrollSpeed * deltaTime);
	spriteTexCoordData[3] -= glm::vec2(0, scrollSpeed * deltaTime);
}
