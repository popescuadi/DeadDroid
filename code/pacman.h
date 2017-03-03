#pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm.hpp>
# include <matrix_transform.hpp>
# include "Shader.h"
//# include "Texture.h"
# include "Model.h"
class pacman
{
public:
	pacman(Shader &shader);
	glm::vec3 pozitie;
	~pacman();
	void DrawPacMan(glm::vec3 position, glm::vec3 color, GLfloat rotate_angle);
private:
	Shader shader;
	Model *container;
	void initializare();
};

