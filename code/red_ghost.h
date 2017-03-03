#pragma once
#include "ghost_interface.h"
class red_ghost :
	public ghost_interface
{
public:
	red_ghost();
	red_ghost(glm::vec3 position,glm::vec3 scale,glm::vec3 color,Shader &shader);
	void DrawGhost();
	~red_ghost();
private:
	void Init();
};

