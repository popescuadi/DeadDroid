#include "Texture.h"



Texture::Texture():Width(0),Height(0),Image_format(GL_RGB),Internal_format(GL_RGB),wrap_s(GL_REPEAT),wrap_t(GL_REPEAT),filter_max(GL_LINEAR),filter_min(GL_LINEAR)
{
	glGenTextures(1, &this->id);
}
void Texture::generate(GLuint width, GLuint height, unsigned char *data)
{
	this->Width = width;
	this->Height = height;
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_format, width, height, 0, this->Image_format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture()
{
}
