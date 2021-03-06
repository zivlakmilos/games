#include "SDL/SDL_image.h"
#include <iostream>
#include <string>

GLuint loadTexture(const std::string &fileName)
{
	SDL_Surface *image = IMG_Load(fileName.c_str());

	SDL_DisplayFormatAlpha(image);

	unsigned object(0);

	glGetTextures(1, &object);

	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTUREWRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	// Free surface
	SDL_FreeSurface(image);

	return object;
}



unsigned int pad_texture = 0;
pad_texture = loadTexture("test.png");

std::cout << pad_texture <<std::endl;

glColor4ub(255, 255, 255, 255)	// White color

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE2D, pad_texture);

// drawing
glTexCoord2d(0, 0); glVertex2f(myX, myY);
glTexCoord2d(1, 0); glVertex2f(myX+width, myY);
glTexCoord2d(1, 1); glVertex2f(myX+width, myY+height);
glTexCoord2d(0, 1); glVertex2f(myX, myY+height);

glDisable(GL_TEXTURE_2D);

// Main loop


/////////////////////////////////////////////////////////////////////


// Disable depth checking
//glDisable(GL_DEPTH_TEST)

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
