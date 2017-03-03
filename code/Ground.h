#pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm.hpp>
# include <matrix_transform.hpp>
# include "Shader.h"
# include "Texture.h"
//# include "camera.h"
class Ground
{
public:
	Ground(Shader &shader_in);
	~Ground();
	void DrawGround(Texture texture, glm::vec3 position, glm::vec3 color);
private:
	GLuint VAO;
	void initGround();
	Shader shader;
};

