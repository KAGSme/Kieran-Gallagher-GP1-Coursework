/*
==========================================================================
cFont.cpp
modified code from lab 8
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cFont.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/
cFont::cFont()
{
	theFont = NULL;
}
/*
==========================================================================
Overloaded constructor
==========================================================================
*/
cFont::cFont(LPCSTR fontFileName, int fontSize)
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}

/*
==========================================================================
Destructor
==========================================================================
*/
cFont::~cFont()
{
	delete theFont;
}
/*
==========================================================================
get the pointer to the font
==========================================================================
*/
FTFont* cFont::getFont()
{
	return theFont;
}

/*
==========================================================================
Render the text using the desired font
==========================================================================
*/
void cFont::printText(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glColor3f(fcRed, fcGreen, fcBlue);
	glScalef(1.0f, -1.0f, 1.0f);
	theFont->Render(text,  -1, textPos);

	glPopMatrix();
}

/*
==========================================================================
Sets the color the font will diplay in 
==========================================================================
*/
void cFont::SetColour(GLfloat red, GLfloat green, GLfloat blue)
{
	fcRed = red;
	fcGreen = green;
	fcBlue = blue;
}
