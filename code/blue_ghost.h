#pragma once
#include "ghost_interface.h"
class blue_ghost :
	public ghost_interface
{
public:
	blue_ghost();
	blue_ghost(glm::vec3 position, glm::vec3 scale, glm::vec3 color, Shader &shader);
	void DrawGhost();
	~blue_ghost();
private:
	void Init();
};

