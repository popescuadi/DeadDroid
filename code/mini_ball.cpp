#include "mini_ball.h"

//glm::vec3 mini_ball::color = 
Model *mini_ball::minge=NULL;

mini_ball::mini_ball()
{
}
mini_ball::mini_ball(glm::vec3 pozition, glm::vec3 scale, Shader &shader)
{
	this->pozition = pozition;
	this->scale = scale;
	this->shader = shader;
	this->Init();
}
void mini_ball::Init()
{
	//this->minge = new Model("C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\tie\\ball.obj");
	if (minge==NULL)
		minge = new Model("C:\\Users\\Adrian\\Documents\\Visual Studio 2015\\Projects\\Game_debate\\Game_debate\\tie\\ball.obj");
}
void mini_ball::DrawBall()
{
	if (vizibil)
	{
		glm::mat4 model;
		model = glm::translate(model, pozition);
		model = glm::scale(model, scale);
		shader.SetMatrix4("model", model, GL_TRUE);
		shader.SetVec3f("color", this->color, GL_TRUE);
		shader.use();
		//minge.Draw(shader);
		Draw(shader);
	}
}
GLboolean mini_ball::vizibilitate(glm::vec3 pac_poz)
{
	if ((pozition.x - 0.1f) < pac_poz.x && (pozition.x + 0.1f) > pac_poz.x)
		if ((pozition.z - 0.1f) < pac_poz.z && (pozition.z + 0.1f) > pac_poz.z)
			vizibil = GL_FALSE;
	if (vizibil==GL_FALSE)
		if (throw_signal == GL_TRUE)
		{
			throw_signal = GL_FALSE;
			return GL_TRUE;
		}
	return GL_FALSE;
}
mini_ball::~mini_ball()
{
}
