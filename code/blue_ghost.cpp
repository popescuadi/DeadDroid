#include "blue_ghost.h"



blue_ghost::blue_ghost()
{
}

blue_ghost::blue_ghost(glm::vec3 position, glm::vec3 scale, glm::vec3 color, Shader &shader) :ghost_interface(position, scale, color, shader)
{
	glewInit();
	this->Init();
	lee_queq_position = 15;
}
void blue_ghost::Init()
{
	ghost = new Model("C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\ghost\\droid.obj");
	this->color = glm::vec3(0.0f, 0.5f, 1.0f);
}
void blue_ghost::DrawGhost()
{
	glm::mat4 model, rotate;
	model = glm::translate(model, position);
	model = glm::scale(model, this->scale);
	model = model;
	shader.SetMatrix4("model", model, GL_TRUE);
	shader.SetVec3f("color", this->color, GL_TRUE);
	shader.use();
	ghost->Draw(shader);
}
blue_ghost::~blue_ghost()
{
}
