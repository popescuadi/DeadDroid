#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "Ground.h"
# include "Labirint.h"
# include "pacman.h"
# include "red_ghost.h"
#include "blue_ghost.h"
# include <iostream>
# include "big_ball.h"
# include <thread>
# include "LeePathFinder.h"
#include "timer.h"
#include "ParticleGenerator.h"
# include "SpriteRender.h"
# include <Windows.h>
enum Game_state
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_PAUSE
};
enum Movement {
	Pause,
	Start,
	Left,
	Right,
	Up,
	Down
};
class Game
{
private:
	Ground *ground;
	Labirint **labirint;
	pacman *pac_man;
	glm::vec3 pac_position;
	GLfloat speed = 0.5f;
	GLfloat pac_angle = 0.0f;
	glm::vec3 last_pac_pos_good;
	GLboolean collision_detec(glm::vec3 ghost_position);
	glm::vec2 x_collision[15];
	glm::vec2 z_collision[15];
	void perimeter_collision_resolution();
	GLboolean full_colision_detection();
	ghost_interface **redGhost;
	GLfloat dt;
	mini_ball **balls=NULL;
	big_ball ** Big_balls = NULL;
	void matrix_to_array(int **matrix, int *&lee_matrix);
	glm::vec3 lee_to_ghost[5];
	void test_matrice()
	{
		int i, j;
		ofstream g;
		g.open("mat.txt", std::ofstream::out);
		for (i = 0;i <= 50;i++)
		{
			for (j = 0;j <= 50;j++)
				g << matrice_pozitii[i][j] << " ";
			g << endl;
		}
	}
	GLboolean pac_death = GL_FALSE;
	timer cronometru;
	ParticleGenerator *particle;
	GLboolean pac_eat_ghost(int j);
	void reset_ghost(int j);
	SpriteRenderer *menu_image;

public:
	void find_lee_path(int ** array_lee, glm::vec3 &poz1, glm::vec3 &poz2, int ghost_number);
	void generare_matirce(int **& matrice_pozitii, glm::vec3 *pozitii, glm::vec3 *scale);
	glm::vec3 pozitii[15];
	glm::vec3 scale[15];
	int **matrice_pozitii;
	int **matrice_pozitii2;
	ResourceManager manager;
	Game();
	Game_state State=GAME_MENU;
	GLboolean keys[1024];
	GLuint Width, Height;
	Game(GLuint width, GLuint height);
	void Init(); 
	void ProcesInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void Death_Render();
	void process_move(Movement mov, GLfloat deltatime);
	void change_music()
	{
		PlaySound(TEXT("scp.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	GLboolean is_pac_allive()
	{
		return pac_death;
	}
	~Game();

};

