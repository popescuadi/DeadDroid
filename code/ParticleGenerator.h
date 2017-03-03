#pragma once
#include <vector>

#include <GL/glew.h>
#include <glm.hpp>

#include "Shader.h"
#include "Texture.h"
# include "pacman.h"
struct Particle {
	glm::vec3 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture texture, GLuint amount);
	void Update(GLfloat dt, pacman &object, GLuint newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f));
	void Draw();
private:
	std::vector<Particle> particles;
	GLuint lastUsedParticle = 0;
	GLuint amount;
	Shader shader;
	Texture texture;
	GLuint VAO;
	void init();
	GLuint firstUnusedParticle();
	void respawnParticle(Particle &particle, pacman &object, glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f));
};
