#include "ghost_interface.h"



ghost_interface::ghost_interface()
{
}
ghost_interface::ghost_interface(glm::vec3 position, glm::vec3 scale, glm::vec3 color,Shader &shader)
{
	this->position = position;
	this->scale = scale;
	this->color = color;
	this->shader = shader;
}
void ghost_interface::get_lee_queq(glm::vec3 *queq)
{
	int i;
	for (i = 0;i <= 4;i++)
	{
		lee_5_queq[i].x = queq[i].x;
		lee_5_queq[i].y = queq[i].y;
		lee_5_queq[i].z = queq[i].z;
	}
	lee_queq_position = 0;
	single_step = GL_FALSE;
}
void ghost_interface::get_lee_pozition(glm::vec3 pos)
{
	next_position = pos;
	single_step = GL_TRUE; 
}
void ghost_interface::step_mode(GLboolean alpha)
{
	single_step = alpha;
}
GLboolean ghost_interface::single_step_mode()
{
	return single_step;
}
void ghost_interface::move(GLfloat dt,glm::vec3 &np)
{
	GLfloat d = 0.002f;
	GLfloat speed = velocity*dt;
	GLfloat x, z;
	x = np.x - position.x;
	z = np.z - position.z;
	if (x > 0)
		position.x += speed;
	if (x < 0)
		position.x -= speed;
	if (z > 0)
		position.z += speed;
	if (z < 0)
		position.z -= speed;
}
void ghost_interface::calculate_next_position(GLfloat dt)
{
		if (single_step == GL_FALSE)
		{
			GLboolean ok = GL_FALSE;
			if ((position.x >(lee_5_queq[lee_queq_position].x - 0.03f) && position.x < lee_5_queq[lee_queq_position].x + 0.03f) && (position.z<lee_5_queq[lee_queq_position].z + 0.03f&&position.z>lee_5_queq[lee_queq_position].z - 0.03f))
			{
				position = lee_5_queq[lee_queq_position];
				lee_queq_position++;
			}
			else
			{
				glm::vec3 a = lee_5_queq[lee_queq_position];
				move(dt, a);
			}
			std::cout << position.x << " " << position.y << " " << position.z << " " << endl;
		}
		else
		{
			if ((position.x > (next_position.x - 0.05f) && position.x < next_position.x + 0.05f) && (position.z<next_position.z + 0.05f&&position.z>next_position.z - 0.05f))
				position = next_position;
			else
				move(dt, next_position);
		}
}
GLboolean ghost_interface::calculate_single_step_ready()
{
	if (position == next_position)
		return GL_TRUE;
	else
		return GL_FALSE;
}
ghost_interface::~ghost_interface()
{
}
