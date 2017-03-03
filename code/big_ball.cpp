#include "big_ball.h"


big_ball::big_ball()
{
}
big_ball::big_ball(glm::vec3 pozition, glm::vec3 scale, Shader &shader):mini_ball(pozition,scale,shader)
{
	//goll
	this->reinitializare();
}
void big_ball::reinitializare()
{
	this->color = glm::vec3(1.0f, 0.0f, 1.0f);
}
big_ball::~big_ball()
{
}
