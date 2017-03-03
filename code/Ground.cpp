#include "Ground.h"



Ground::Ground(Shader &shader_in )
{
	this->shader = shader_in;
	this->initGround();
}
void Ground::initGround()
{
	GLfloat planeVertices[] = {
		5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
	};
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
void Ground::DrawGround(Texture texture,glm::vec3 position,glm::vec3 color)
{
	shader.use();
	glm::mat4 model;
	model = glm::translate(model,position);
	model = glm::scale(model, glm::vec3(0.5f,0.5f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	this->shader.SetVec3f("color", color,GL_TRUE);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Ground::~Ground()
{
}
