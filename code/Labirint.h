#pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm.hpp>
# include <matrix_transform.hpp>
# include "Shader.h"
# include "Texture.h"
class Labirint
{
public:
	Labirint(Shader &shader_in);
	Labirint();
	void LabDraw(Texture &texture, glm::vec3 position, glm::vec3 color,glm::vec3 scale_vec,GLboolean rotate);
	~Labirint();
private:
	GLuint VAO;
	Shader shader;
	void init();
};

