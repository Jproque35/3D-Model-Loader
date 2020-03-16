#include "skyboxLoader.h"

skyboxLoader::skyboxLoader() {

}

skyboxLoader::~skyboxLoader() {

}

/*
Load wall textures
*/
void skyboxLoader::loadTextures() {
	tex_id[0] = SOIL_load_OGL_texture
		(
		"cm_front.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	tex_id[1] = SOIL_load_OGL_texture
		(
		"cm_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	tex_id[2] = SOIL_load_OGL_texture
		(
		"cm_back.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	tex_id[3] = SOIL_load_OGL_texture
		(
		"cm_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	tex_id[4] = SOIL_load_OGL_texture
		(
		"cm_top.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	tex_id[5] = SOIL_load_OGL_texture
		(
		"cm_bottom.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


}

/*
Draw our walls
*/
void skyboxLoader::draw()
{
	//Draw all our walls

	glBindTexture(GL_TEXTURE_2D, tex_id[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10, -10, -10);
	glTexCoord2f(1, 0); glVertex3f(+10, -10, -10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, -10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, -10);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex_id[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(10, -10, -10);
	glTexCoord2f(1, 0); glVertex3f(10, -10, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, 10);
	glTexCoord2f(0, 1); glVertex3f(10, 10, -10);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex_id[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(10, -10, 10);
	glTexCoord2f(1, 0); glVertex3f(-10, -10, 10);
	glTexCoord2f(1, 1); glVertex3f(-10, 10, 10);
	glTexCoord2f(0, 1); glVertex3f(10, 10, 10);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex_id[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10, -10, 10);
	glTexCoord2f(1, 0); glVertex3f(-10, -10, -10);
	glTexCoord2f(1, 1); glVertex3f(-10, 10, -10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, 10);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex_id[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10, 10, -10);
	glTexCoord2f(1, 0); glVertex3f(10, 10, -10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, 10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, 10);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex_id[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3f(10, -10, -10);
	glTexCoord2f(0, 1); glVertex3f(-10, -10, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, -10, 10);
	glTexCoord2f(1, 0); glVertex3f(10, -10, 10);
	glEnd();
}