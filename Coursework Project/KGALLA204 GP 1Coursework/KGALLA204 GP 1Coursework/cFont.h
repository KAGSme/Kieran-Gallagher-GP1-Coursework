/*
==========================================================================
cFont.h
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
	cFont();
	cFont(LPCSTR fontFileName, int fontSize);
	~cFont();
	FTFont* getFont();
	void printText(LPCSTR text, FTPoint textPos);
	void cFont::SetColour(GLfloat red, GLfloat green, GLfloat blue);

};
#endif