#pragma once
# include <GL/glew.h>
class Texture
{
public:
	GLuint id;
	GLuint wrap_s,wrap_t;
	GLuint Internal_format, Image_format;
	GLuint Width, Height;
	GLuint filter_min, filter_max;
	Texture();
	void generate(GLuint width, GLuint height, unsigned char *data);
	void bind();
	void unbind();
	~Texture();
};

