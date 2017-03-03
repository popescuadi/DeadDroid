#pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm.hpp>
# include <matrix_transform.hpp>
# include "Shader.h"
# include "Texture.h"
# include "Model.h"
//# include "utils.h"

class ghost_interface
{
public:
	GLfloat velocity = 0.5f;
	ghost_interface();
	ghost_interface(glm::vec3 position, glm::vec3 scale,glm::vec3 color,Shader &shader);
	virtual ~ghost_interface();
	virtual void DrawGhost()=0;
	glm::vec3 lee_5_queq[5];
	int lee_queq_position = 15;
	GLboolean single_step_mode();
	void step_mode(GLboolean alpha);
	void get_lee_queq(glm::vec3 *queq);
	void get_lee_pozition(glm::vec3 pos);
	void calculate_next_position(GLfloat dt);
	void move(GLfloat dt, glm::vec3 &np);
	GLboolean calculate_single_step_ready();
	glm::vec3 position;
protected:
	virtual void Init()=0;
	glm::vec3 scale;
	glm::vec3 color;
	Model *ghost;
	Shader shader;
	glm::vec3 next_position;
	GLboolean single_step = GL_FALSE;
};

