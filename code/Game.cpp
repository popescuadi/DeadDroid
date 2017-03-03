#include "Game.h"



Game::Game()
{
}
Game::Game(GLuint width, GLuint height)
{
	Width = width;
	Height = height;
	int i, j;
	matrice_pozitii = new int *[51];
	for (i = 0;i <= 50;i++)
		matrice_pozitii[i] = new int[51];
}
void Game::Init()
{
	PlaySound(TEXT("got.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	pozitii[0]= glm::vec3(0.0f, 0.0f, 0.0f);
	pozitii[1] = glm::vec3(2.5f, -0.07f, 0.0f);
	pozitii[2] = glm::vec3(0.0f, -0.07f, 2.4f);
	pozitii[3] = glm::vec3(-2.5f, -0.07f, 0.0f);
	pozitii[4] = glm::vec3(0.0f, -0.07f, -2.4f);
	pozitii[5] = glm::vec3(0.0f, -0.0701f, -2.0f);
	pozitii[6] = glm::vec3(0.0f, -0.0701f, 2.0f);
	pozitii[7] = glm::vec3(0.0f, -0.07f, -1.1f);
	pozitii[8] = glm::vec3(1.5f, -0.07f, 0.4f);
	pozitii[9] = glm::vec3(-1.5f, -0.07f, 0.4f);
	scale[0]= glm::vec3(0.2f, 0.4f, 5.f);
	scale[1]= glm::vec3(5.0f, 0.4f, 0.2f);
	scale[2]= glm::vec3(0.2f, 0.4f, 5.f);
	scale[3] = glm::vec3(5.0f, 0.4f, 0.2f);
	scale[4] = glm::vec3(0.2f, 0.4f, 0.8f);
	scale[5] = glm::vec3(0.2f, 0.4f, 0.8f);
	scale[6] = glm::vec3(2.0f, 0.4f, 0.2f);
	scale[7] = glm::vec3(0.2f, 0.4f, 2.0f);
	scale[8] = glm::vec3(0.2f, 0.4f, 2.0f);
	std::thread matrix_thread([&] {this->generare_matirce(this->matrice_pozitii, this->pozitii, this->scale);});
	perimeter_collision_resolution();
	pac_position = glm::vec3(1.95f, 0.0f, 0.69f);
	manager.LoadShader("vertex.txt", "fragment.txt", "prime");
	manager.LoadShader("vert1.txt", "frag1.txt", "second");
	manager.LoadTexture("poza1.png",GL_TRUE,"ground_image");
	manager.LoadTexture("android.png", GL_TRUE, "menu");
	manager.LoadTexture("labirint.png", GL_TRUE, "lab_imag");
	manager.LoadShader("menu_vertex.txt", "menu_fragment.txt", "menu");
	menu_image = new SpriteRenderer(manager.GetShader("menu"));
	ground = new Ground(manager.GetShader("prime"));
	labirint = new Labirint *[15];
	int i;
	for (i = 0;i <= 15;i++)
		labirint[i] = new Labirint(manager.GetShader("prime"));
	pac_man = new pacman(manager.GetShader("second"));
	redGhost = new ghost_interface *[2];
	redGhost[0] = new red_ghost(glm::vec3 (0.5f,0.0f,1.5f) ,glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), manager.GetShader("second"));
	redGhost[1]= new blue_ghost(glm::vec3 (-1.5f, 0.0f, 1.8f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), manager.GetShader("second"));
	balls = new mini_ball *[14];
	balls[0] = new mini_ball(glm::vec3(1.95f, 0.0f, 0.69f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[1] = new mini_ball(glm::vec3(1.95f, 0.0f, -0.97f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[2] = new mini_ball(glm::vec3(1.95f, 0.0f, 1.80f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[3] = new mini_ball(glm::vec3(0.75f, 0.0f, 1.80f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[4] = new mini_ball(glm::vec3(0.75f, 0.0f, 0.190f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[5] = new mini_ball(glm::vec3(-0.78f, 0.0f, 0.190f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[6] = new mini_ball(glm::vec3(-0.78f, 0.0f, 1.83f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[7] = new mini_ball(glm::vec3(-1.96f, 0.0f, 1.92f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[8] = new mini_ball(glm::vec3(-1.96f, 0.0f, -1.75f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[9] = new mini_ball(glm::vec3(-0.64f, 0.0f, -1.75f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[10] = new mini_ball(glm::vec3(-0.64f, 0.0f, -1.38f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[11] = new mini_ball(glm::vec3(0.43f, 0.0f, -1.38f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[12] = new mini_ball(glm::vec3(0.43f, 0.0f, -1.88f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	balls[13] = new mini_ball(glm::vec3(1.74f, 0.0f, -1.88f), glm::vec3(0.001f, 0.001f, 0.001f), manager.GetShader("second"));
	Big_balls = new big_ball *[5];
	Big_balls[0] = new big_ball(glm::vec3(1.32f, 0.0f,-0.83f), glm::vec3(0.0025f, 0.0025f, 0.0025f), manager.GetShader("second"));
	Big_balls[1] = new big_ball(glm::vec3(-1.33f, 0.0f, -0.83f), glm::vec3(0.0025f, 0.0025f, 0.0025f), manager.GetShader("second"));
	Big_balls[2] = new big_ball(glm::vec3(0.072f, 0.0f, 0.44f), glm::vec3(0.0025f, 0.0025f, 0.0025f), manager.GetShader("second"));
	Big_balls[3] = new big_ball(glm::vec3(-1.33f, 0.0f, 1.62f), glm::vec3(0.0025f, 0.0025f, 0.0025f), manager.GetShader("second"));
	Big_balls[4] = new big_ball(glm::vec3(1.32f, 0.0f, 1.66f), glm::vec3(0.0025f, 0.0025f, 0.0025f), manager.GetShader("second"));
	matrix_thread.join();
	test_matrice();
	matrice_pozitii2 = new int*[51];
	for (int i = 0;i <= 50;i++)
	{
		matrice_pozitii2[i] = new int[51];
		for (int j = 0;j <= 50;j++)
			matrice_pozitii2[i][j] = matrice_pozitii[i][j];
	}
}
GLboolean Game::pac_eat_ghost(int j)
{
	if (sqrt((redGhost[j]->position.x - pac_position.x)*(redGhost[j]->position.x - pac_position.x) + (redGhost[j]->position.z - pac_position.z)*(redGhost[j]->position.z - pac_position.z)) <= 0.1f)
		return GL_TRUE;
	else
		return GL_FALSE;
}
void Game::reset_ghost(int j)
{
	glm::vec3 a[4];
	a[0] = glm::vec3(-1.5f, 0.0f, -1.5f);
	a[1] = glm::vec3(0.5f, 0.0f, 1.5f);
	a[2] = glm::vec3(1.5f, 0.0f, -1.5f);
	a[3] = glm::vec3(-1.5f, 0.0f, 1.8f);
	srand(time(NULL));
	int random = rand() % 4;
	redGhost[j]->position = a[random];
	redGhost[j]->lee_queq_position = 15;
}
void Game::ProcesInput(GLfloat dt)
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("menu").SetInteger("image", 0,GL_TRUE);       //SetInteger("image", 0);
	ResourceManager::GetShader("menu").SetMatrix4("projection", projection,GL_TRUE);
	menu_image->DrawSprite(manager.GetTexture("menu"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
}
void Game::Update(GLfloat dt)
{
	//text->RenderText("la la la", Width / 2, Height / 2,2);
}
void Game::Render()
{
	std::thread *lee_thread = NULL;
	glm::vec3 color(0.0f, 1.0f, 0.0f);
	if (!cronometru.wait())
	{
		for (int j = 0;j <= 1;j++)
		{
			if (redGhost[j]->single_step_mode() == GL_FALSE)
			{
				if (redGhost[j]->lee_queq_position >= 5)
				{
					glm::vec3 a = redGhost[j]->position;
					glm::vec3 b = pac_position;
					if (j==0)
						//lee_thread = new std::thread([&] {this->find_lee_path(this->matrice_pozitii, a, b,j);});
						find_lee_path(this->matrice_pozitii, a, b,j);
					else
						lee_thread = new std::thread([&] {this->find_lee_path(this->matrice_pozitii2, a, b, j);});
					//find_lee_path(this->matrice_pozitii, a, b);
				}
			}
			else
			{
				if (redGhost[j]->calculate_single_step_ready() == GL_TRUE)
				{
					glm::vec3 a = redGhost[j]->position;
					glm::vec3 b = pac_position;
					if (j == 0)
						//lee_thread = new std::thread([&] {this->find_lee_path(this->matrice_pozitii, a, b, j);});
						find_lee_path(this->matrice_pozitii, a, b, j);
					else
						lee_thread = new std::thread([&] {this->find_lee_path(this->matrice_pozitii2, a, b, j);});
					//find_lee_path(this->matrice_pozitii, a, b);
				}
			}
		}
	}
	ground->DrawGround(manager.GetTexture("ground_image"), pozitii[0], color);
	labirint[0]->LabDraw(manager.GetTexture("lab_imag"), pozitii[1], color,scale[0] ,GL_FALSE);
	labirint[1]->LabDraw(manager.GetTexture("lab_imag"), pozitii[2], color, scale[1], GL_FALSE);
	labirint[2]->LabDraw(manager.GetTexture("lab_imag"), pozitii[3], color, scale[2], GL_FALSE);
	labirint[3]->LabDraw(manager.GetTexture("lab_imag"), pozitii[4], color, scale[3], GL_FALSE);
	labirint[4]->LabDraw(manager.GetTexture("lab_imag"), pozitii[5], color, scale[4], GL_FALSE);
	labirint[5]->LabDraw(manager.GetTexture("lab_imag"), pozitii[6], color, scale[5], GL_FALSE);
	labirint[6]->LabDraw(manager.GetTexture("lab_imag"), pozitii[7], color, scale[6], GL_FALSE);
	labirint[7]->LabDraw(manager.GetTexture("lab_imag"), pozitii[8], color, scale[7], GL_FALSE);
	labirint[8]->LabDraw(manager.GetTexture("lab_imag"), pozitii[9], color, scale[8], GL_FALSE);
	if (full_colision_detection())
	{
		pac_man->DrawPacMan(pac_position, glm::vec3(0.0f, 1.0f, 0.0f), pac_angle);
		last_pac_pos_good = pac_position;
	}
	else
	{
		pac_man->DrawPacMan(last_pac_pos_good, glm::vec3(0.0f, 1.0f, 0.0f), pac_angle);
		pac_position = last_pac_pos_good;
	}
	for (int i = 0;i < 14;i++)
	{
		balls[i]->vizibilitate(pac_position);
		balls[i]->DrawBall();
	}
	for (int i = 0;i < 5;i++)
	{
		if (Big_balls[i]->vizibilitate(pac_position))
			cronometru.set_clock(3);
		Big_balls[i]->DrawBall();
	}
	if (lee_thread != NULL)
	{
		lee_thread->join();
		delete lee_thread;
		lee_thread = NULL;
	}

	if (!cronometru.wait())
	{
		redGhost[0]->calculate_next_position(dt);
		redGhost[1]->calculate_next_position(dt);
	}
	redGhost[0]->DrawGhost();
	redGhost[1]->DrawGhost();
	//particle->Update(dt, *pac_man, 4, glm::vec3(0.2f, 0.5f, 0.2f));
	GLboolean verify = GL_TRUE;
	for (int i = 0;i < 14;i++)
	{
		if (balls[i]->vizibil == GL_TRUE)
		{
			verify = GL_FALSE;
			break;
		}
	}
	if (verify == GL_TRUE)
		for (int i = 0;i < 14;i++)
			balls[i]->vizibil = GL_TRUE;
	for (int i = 0;i <= 1;i++)
		if (pac_eat_ghost(i) == GL_TRUE&&cronometru.wait())
			reset_ghost(i);
}
void Game::Death_Render()
{
	glm::vec3 color(0.0f, 1.0f, 0.0f);
	ground->DrawGround(manager.GetTexture("ground_image"), pozitii[0], color);
	labirint[0]->LabDraw(manager.GetTexture("lab_imag"), pozitii[1], color, scale[0], GL_FALSE);
	labirint[1]->LabDraw(manager.GetTexture("lab_imag"), pozitii[2], color, scale[1], GL_FALSE);
	labirint[2]->LabDraw(manager.GetTexture("lab_imag"), pozitii[3], color, scale[2], GL_FALSE);
	labirint[3]->LabDraw(manager.GetTexture("lab_imag"), pozitii[4], color, scale[3], GL_FALSE);
	labirint[4]->LabDraw(manager.GetTexture("lab_imag"), pozitii[5], color, scale[4], GL_FALSE);
	labirint[5]->LabDraw(manager.GetTexture("lab_imag"), pozitii[6], color, scale[5], GL_FALSE);
	labirint[6]->LabDraw(manager.GetTexture("lab_imag"), pozitii[7], color, scale[6], GL_FALSE);
	labirint[7]->LabDraw(manager.GetTexture("lab_imag"), pozitii[8], color, scale[7], GL_FALSE);
	labirint[8]->LabDraw(manager.GetTexture("lab_imag"), pozitii[9], color, scale[8], GL_FALSE);
	pac_man->DrawPacMan(pac_position, glm::vec3(0.0f, 1.0f, 0.0f), pac_angle);
	redGhost[0]->DrawGhost();
	redGhost[1]->DrawGhost();
}
void Game::process_move(Movement mov, GLfloat deltatime)
{
	if (pac_death == GL_FALSE)
	{
		GLfloat velocity = speed*deltatime;
		dt = deltatime;
		if (mov == Up)
		{
			pac_position.z -= velocity;
			pac_angle = 0.0f;
		}
		if (mov == Down)
		{
			pac_position.z += velocity;
			pac_angle = 0.0f;
		}
		if (mov == Left)
		{
			pac_position.x -= velocity;
			pac_angle = 90.0f;
		}
		if (mov == Right)
		{
			pac_position.x += velocity;
			pac_angle = 90.0f;
		}
	}
}
GLboolean Game::collision_detec(glm::vec3 ghost_position)
{
	for (int i = 0;i <= 8;i++)
	{
		if (ghost_position.x > (x_collision[i].x - x_collision[i].y - 0.1f) && ghost_position.x < (x_collision[i].x + x_collision[i].y + 0.1f))
		{
			if (ghost_position.z > (z_collision[i].x - z_collision[i].y - 0.1f) && ghost_position.z < (z_collision[i].x + z_collision[i].y + 0.1f))
			{
				return GL_FALSE;
			}
		}
	}
	return GL_TRUE;
}
void Game::perimeter_collision_resolution()
{
	for (int i = 1;i <= 9;i++)
	{
		x_collision[i - 1].x = pozitii[i].x;
		x_collision[i - 1].y = scale[i - 1].x / (2.0f);
		z_collision[i - 1].x = pozitii[i].z;
		z_collision[i - 1].y = scale[i - 1].z / (2.0f);
	}
}
GLboolean Game::full_colision_detection()
{
	int i;
	for (i = 0;i <= 8;i++)
	{
		if (pac_position.x > (x_collision[i].x - x_collision[i].y - 0.15f) && pac_position.x < (x_collision[i].x + x_collision[i].y + 0.15f))
		{
			if (pac_position.z > (z_collision[i].x - z_collision[i].y - 0.15f) && pac_position.z < (z_collision[i].x + z_collision[i].y + 0.15f))
			{
				if (pac_angle==95.0f)
					last_pac_pos_good.z = pac_position.z;
				if (pac_angle == 0.0f)
					last_pac_pos_good.x = pac_position.x;
				return GL_FALSE;
			}
		}
	}
	return GL_TRUE;
}
void Game::generare_matirce(int **& matrice_pozitii, glm::vec3 *pozitii, glm::vec3 *scale)
{
	GLint poz_inf1,poz_sup1,distanta, poz_inf2, poz_sup2;
	GLfloat aux;
	for (int i = 0;i <= 50;i++)
		for (int j = 0;j <= 50;j++)
			matrice_pozitii[i][j] = 0;
	for (int i = 1;i <= 9;i++)
	{
		aux = pozitii[i].x;
		aux = aux * 10;
		poz_inf1 = aux;
		poz_inf1 = poz_inf1 + 25;
		aux = scale[i - 1].x;
		aux = aux * 10;
		distanta = aux;
		poz_sup1 = poz_inf1 + distanta/2+1;
		poz_inf1 = poz_inf1 - distanta / 2-1;
		if (poz_inf1 < 0)
			poz_inf1 = 0;
		if (poz_sup1 > 50)
			poz_sup1 = 50;
		aux = pozitii[i].z;
		aux = aux * 10;
		poz_inf2 = aux;
		poz_inf2 = poz_inf2 + 25;
		aux = scale[i - 1].z;
		aux = aux * 10;
		distanta = aux;
		poz_sup2 = poz_inf2 + distanta / 2+1;
		poz_inf2 = poz_inf2 - distanta / 2-1;
		if (poz_inf2 < 0)
			poz_inf2 = 0;
		if (poz_sup2 > 50)
			poz_sup2 = 50;
		for (int j2 = poz_inf2;j2 <= poz_sup2;j2++)
			for (int j1 = poz_inf1;j1 <= poz_sup1;j1++)
				matrice_pozitii[j2][j1] = 1;
	}
}
void Game::matrix_to_array(int **matrix,int *&lee_matrix)
{
	int i, j, k = 0;
	for (i = 0;i <= 50;i++)
		for (j = 0;j <= 50;j++)
		{
			lee_matrix[k] = matrix[i][j];
			k++;
		}
}
void Game::find_lee_path(int ** array_lee, glm::vec3 &poz1, glm::vec3 &poz2,int ghost_number)
{
	int *lee_matrix = NULL;
	lee_matrix = new int[51 * 51];
	int x1, y1,x2,y2;
	x1 = poz1.x * 10+25;
	y1 = poz1.z * 10 + 25;
	array_lee[y1][x1] = 2;
	x2 = poz2.x * 10 + 25;
	y2 = poz2.z * 10 + 25;
	array_lee[y2][x2] = 3;
	test_matrice();
	matrix_to_array(array_lee,lee_matrix);
	LeePathfinder path_finder(lee_matrix, 51, 51);
	CoordVector *lee_queq = path_finder.CalculatePath();
	array_lee[y1][x1] = 0;
	array_lee[y2][x2] = 0;
	if (lee_queq->size() > 0)
	{
		if (lee_queq->size() > 5)
		{
			int k = 0;
			GLfloat aux;
			for (auto j = lee_queq->size() - 1;j >= 0;j--)
			{
				aux = (*lee_queq)[j].first - 25;
				aux = aux / 10;
				lee_to_ghost[k].x = aux;
				lee_to_ghost[k].y = 0.0f;
				aux = (*lee_queq)[j].second - 25;
				aux = aux / 10;
				lee_to_ghost[k].z = aux;
				k++;
				std::cout << lee_to_ghost[k].x << " " << lee_to_ghost[k].y << " " << lee_to_ghost[k].z << endl;
				if (k == 5)
					break;
			}
			redGhost[ghost_number]->get_lee_queq(lee_to_ghost);
		}
		else
		{
			GLfloat aux;
			aux = (*lee_queq)[0].first - 25;
			aux = aux / 10;
			lee_to_ghost[0].x = aux;
			lee_to_ghost[0].y = 0.0f;
			aux = (*lee_queq)[0].second - 25;
			aux = aux / 10;
			lee_to_ghost[0].z = aux;
			redGhost[ghost_number]->get_lee_pozition(lee_to_ghost[0]);
		}
	}
	if (lee_queq->size() >=0 && lee_queq->size()<=1)
	{
		redGhost[ghost_number]->get_lee_pozition(pac_position);
		pac_death = GL_TRUE;
		PlaySound(TEXT("piano.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
}
Game::~Game()
{
	//engine->drop();
}
