#include "red_ghost.h"



red_ghost::red_ghost()
{
}
red_ghost::red_ghost(glm::vec3 position, glm::vec3 scale, glm::vec3 color,Shader &shader):ghost_interface(position,scale,color,shader)
{
	glewInit();
	this->Init();
	lee_queq_position = 15;
}
void red_ghost::Init()
{
	ghost = new Model("C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\ghost\\droid.obj");
}
void red_ghost::DrawGhost()
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

red_ghost::~red_ghost()
{
}
