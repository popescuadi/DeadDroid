#pragma once
#include "mini_ball.h"
class big_ball :
	public mini_ball
{
public:
	big_ball();
	big_ball(glm::vec3 pozition, glm::vec3 scale, Shader &shader);
	~big_ball();
private:
	void reinitializare();
};

