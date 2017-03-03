#pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm.hpp>
# include <matrix_transform.hpp>
# include "Shader.h"
//# include "Texture.h"
# include "Model.h"
class mini_ball
{
public:
	mini_ball();
	mini_ball(glm::vec3 pozition, glm::vec3 scale, Shader &shader);
	void DrawBall();
	GLboolean throw_signal = GL_TRUE;
	GLboolean vizibilitate(glm::vec3 pac_pos);
	~mini_ball();
	GLboolean vizibil = GL_TRUE;
protected:
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	Shader shader;
	static void Draw(Shader &shad)
	{
		minge->Draw(shad);
	}
	void Init();
	static Model *minge;
	glm::vec3 pozition;
	glm::vec3 scale;
};

