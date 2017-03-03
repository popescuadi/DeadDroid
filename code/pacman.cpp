#include "pacman.h"



pacman::pacman(Shader &shader)
{
	this->shader = shader;
	initializare();
}
void pacman::initializare()
{
	//"C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\Robot"
	container = new Model("C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\scar\\droid.obj");
}
void pacman::DrawPacMan(glm::vec3 position, glm::vec3 color, GLfloat rotate_angle)
{
	glm::mat4 model, rotate;
	pozitie = position;
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	rotate = glm::rotate(rotate, glm::radians(rotate_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate = glm::rotate(rotate, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = model*rotate;
	shader.SetMatrix4("model", model, GL_TRUE);
	shader.SetVec3f("color", color, GL_TRUE);
	shader.use();
	container->Draw(shader);
}
pacman::~pacman()
{
}
