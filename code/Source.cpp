#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ground.h"
#include "Game.h"
# include <iostream>
# include "camera.h"

GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
void callback_key(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
GLuint screen_w = 800;
GLuint screen_h = 600;
Game breakout(screen_w, screen_h);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
Camera  camera(glm::vec3(0.0f, 2.0f, 3.0f));
GLfloat lastX = screen_w / 2.0;
GLfloat lastY = screen_h / 2.0;
bool    keys[1024];
int change_mp3 = 0;
int nr = 0;
int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(screen_w, screen_h, "Game Debate", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glfwInit();
	glGetError();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, screen_w, screen_h);
	glfwSetKeyCallback(window, callback_key);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	breakout.Init();
	breakout.State = GAME_MENU;
	while (!glfwWindowShouldClose(window))
	{
		if (change_mp3 == 1 && nr == 0)
		{
			breakout.change_music();
			nr++;
		}
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		glClearColor(0.5f, 0.5f, 0.1f, 0.1f);
		if (breakout.is_pac_allive() == GL_TRUE)
			glClearColor(0.5f, 0.5f, 0.9f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screen_w / (float)screen_h, 0.1f, 100.0f);
		breakout.manager.GetShader("prime").SetMatrix4("projection", projection,GL_TRUE);
		breakout.manager.GetShader("prime").SetMatrix4("view",view, GL_TRUE);
		breakout.manager.GetShader("prime").SetVec2f("zbuffer", glm::vec2(0.0f, 0.0f), GL_TRUE);
		breakout.manager.GetShader("second").SetMatrix4("projection", projection, GL_TRUE);
		breakout.manager.GetShader("second").SetMatrix4("view", view, GL_TRUE);
		breakout.manager.GetShader("second").SetVec2f("zbuffer", glm::vec2(0.0f, 0.0f), GL_TRUE);
		breakout.manager.GetShader("menu").SetMatrix4("projection", projection, GL_TRUE);
		breakout.manager.GetShader("menu").SetMatrix4("view", view, GL_TRUE);
		if (breakout.State == GAME_PAUSE)
		{
			breakout.Death_Render();
		}
		if (breakout.State == GAME_ACTIVE)
		{
			do_movement();
			if (breakout.is_pac_allive() == GL_TRUE)
			{
				breakout.manager.GetShader("prime").SetVec2f("zbuffer", glm::vec2(1.0f, 0.0f), GL_TRUE);
				breakout.manager.GetShader("second").SetVec2f("zbuffer", glm::vec2(1.0f, 0.0f), GL_TRUE);
			}
			breakout.Update(deltaTime);
			if (breakout.is_pac_allive() == GL_FALSE)
			{
				breakout.Render();
			}
			if (breakout.is_pac_allive() == GL_TRUE)
				breakout.Death_Render();
		}
		if (breakout.State == GAME_MENU)
		{
			breakout.ProcesInput(deltaTime);
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
void callback_key(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			breakout.keys[key] = GL_TRUE;
			keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE)
		{
			breakout.keys[key] = GL_FALSE;
			keys[key] = GL_FALSE;
		}
	}
	if (key == GLFW_KEY_ENTER&&action == GLFW_PRESS)
	{
		breakout.State = GAME_ACTIVE;
		change_mp3 = 1;
	}
	if (key == GLFW_KEY_P&&action == GLFW_PRESS)
	{
		int x = 0;
		if (breakout.State == GAME_ACTIVE)
		{
			breakout.State = GAME_PAUSE;
			x = 1;
		}
		if (breakout.State == GAME_PAUSE&&x==0)
			breakout.State = GAME_ACTIVE;
	}
}
void do_movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_UP])
		breakout.process_move(Up, deltaTime);
	if (keys[GLFW_KEY_DOWN])
		breakout.process_move(Down, deltaTime);
	if (keys[GLFW_KEY_LEFT])
		breakout.process_move(Left, deltaTime);
	if (keys[GLFW_KEY_RIGHT])
		breakout.process_move(Right, deltaTime);
}
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, screen_w, screen_h, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screen_w, screen_h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}