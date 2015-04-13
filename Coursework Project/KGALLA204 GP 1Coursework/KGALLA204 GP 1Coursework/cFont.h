/*
==========================================================================
cFont.h
modified code from lab 8
==========================================================================
*/

#ifndef _CFONT_H
#define _CFONT_H

// OpenGL Headers
#include "GameConstants.h"

using namespace std;

class cFont
{
private:
	FTFont* theFont;
	GLfloat fcRed = 255;
	GLfloat fcGreen = 255;
	GLfloat fcBlue = 255;

public:
	cFont();//Default Constructor
	cFont(LPCSTR fontFileName, int fontSize);//Overloaded constructor
	~cFont();//Destructor
	FTFont* getFont();//get the pointer to the font
	void printText(LPCSTR text, FTPoint textPos);//Render the text using the desired font
	void cFont::SetColour(GLfloat red, GLfloat green, GLfloat blue); //Sets the color the font will diplay in 

};
#endif