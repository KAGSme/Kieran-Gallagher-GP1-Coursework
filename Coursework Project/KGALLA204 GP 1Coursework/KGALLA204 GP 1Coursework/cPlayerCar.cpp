/*
=================
cPlayerCar.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayerCar.h"

cPlayerCar::cPlayerCar()
{
	isAlive = true;
}

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
	engineEffectTimer += deltaTime;

	setBoundingRect(&boundingRect);
	//renderCollisionBox();
	//loops engine sound effect every 0.27 seconds
	if (engineEffectTimer >= 0.27f)
	{
		m_SoundMgr->getSnd("Engine")->playAudio(AL_TRUE);
		engineEffectTimer = 0;
	}
	//move right(keyboard)--------------------------
	if (m_InputMgr->isKeyDown(VK_RIGHT) && spritePos2D.x < boundryX[1])
	{
		spritePos2D.x += speedX * float(deltaTime);
		spriteRotation = 10.0f;

	}
	//move right(gamepad)-------------------------------
	if (m_InputMgr->getController(0).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && spritePos2D.x < boundryX[1])
	{
		spritePos2D.x += speedX * float(deltaTime);
		spriteRotation = 10.0f;
		dpadRight = true;
	}
	else dpadRight = false;
	//move left(keyboard)-----------------------------------
	if (m_InputMgr->isKeyDown(VK_LEFT)  && spritePos2D.x > boundryX[0])
	{
		spritePos2D.x -= speedX * deltaTime;
		spriteRotation = -10.0f;
	}
	//move left(gamepad)------------------------------------
	if (m_InputMgr->getController(0).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && spritePos2D.x > boundryX[0])
	{
		spritePos2D.x -= speedX * deltaTime;
		spriteRotation = -10.0f;
		dpadLeft = true;
	}
	else dpadLeft = false;
	//resets sprite rotation-------------------------------
	if (!m_InputMgr->isKeyDown(VK_LEFT) && !m_InputMgr->isKeyDown(VK_RIGHT))
	{
		if (!dpadLeft && !dpadRight)
		{
			spriteRotation = 0.0f;
		}
	}

	if (playerHealth > 0)
	{
		isAlive = true;
	}
	//plays failure sound and sets player to not active if health is 0
	if (playerHealth <= 0 && isAlive)
	{
		m_SoundMgr->getSnd("Failure")->playAudio(AL_TRUE);
		setActive(false);
		cout << "\n Player Dead!";
	}
	//sets vibration of motors
	m_InputMgr->getController(0).Vibrate(vibrateStrength, vibrateStrength);
	//resets vibration to zero after half a second
	if (vibrateStrength > 0)
	{
		vibrateTimer += deltaTime;
		if (vibrateTimer > 0.5f) 
		{ 
			vibrateStrength = 0; 
			vibrateTimer = 0;
		}
	}
}
//sets speed of cars speed along x-axis
void cPlayerCar::SetSpeedX(float velX)
{
	speedX = velX;
}
//sets the boundries the player abides by and can't pass
void cPlayerCar::SetBoundriesX(float boundriesX1, float boundriesX2)
{
	boundryX[0] = boundriesX1;
	boundryX[1] = boundriesX2;
}
//reduces health of player, plays sound effect and increases vibration in controller
void cPlayerCar::ReduceHealth()
{
	playerHealth--;
	m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
	cout << "\n Health Decrease!";
	vibrateStrength = 3000;
}
//sets the player health
void cPlayerCar::SetPlayerHealth(int value)
{
	playerHealth = value;
}
//returns player health
int cPlayerCar::GetPlayerHealth()
{
	return playerHealth;
}
