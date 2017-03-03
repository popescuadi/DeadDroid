#include "Shader.h"



Shader::Shader()
{
}
void Shader::Compile(const GLchar *vertex,const GLchar *fragment,const GLchar *geometry)
{
	GLuint vertexShader, fragmentShader;
	GLuint geometryShader;
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	CeckCompileErrors(vertexShader, "VERTEX");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	CeckCompileErrors(vertexShader, "FRAGMENT");
	if (geometry!=nullptr)
	{

		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometry, NULL);
		glCompileShader(geometryShader);
		CeckCompileErrors(geometryShader, "GEOMETRY");
	}
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	if (geometry != nullptr)
		glAttachShader(this->Program, geometryShader);
	glLinkProgram(this->Program);
	CeckCompileErrors(this->Program, "PROGRAM");
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometry != nullptr)
		glDeleteShader(geometryShader);
}
void Shader::use()
{
	glUseProgram(this->Program);
}
void Shader::SetFloat(const GLchar* nume, GLfloat x, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform1f (glGetUniformLocation(this->Program, nume), x);
}
void Shader::SetInteger(const GLchar* nume, GLint x, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform1i(glGetUniformLocation(this->Program, nume), x);
}
void Shader::SetVec2f(const GLchar* nume, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->Program, nume), x, y);
}
void Shader::SetVec2f(const GLchar* nume,const glm::vec2 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->Program, nume), value.x,value.y);
}
void Shader::SetVec3f(const GLchar* nume, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->Program, nume), x, y,z);
}
void Shader::SetVec3f(const GLchar* nume,const  glm::vec3 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->Program, nume), value.x, value.y,value.z);
}
void Shader::SetVec4f(const GLchar* nume, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->Program, nume), x, y, z,w);
}
void Shader::SetVec4f(const GLchar *nume, const glm::vec4 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->Program, nume), value.x, value.y, value.z,value.w);
}
void Shader::SetMatrix4(const GLchar* nume, const glm::mat4 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniformMatrix4fv(glGetUniformLocation(this->Program, nume),1, GL_FALSE, glm::value_ptr(value));
}
void Shader::CeckCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infolog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infolog);
			std::cout << "eroare de compilare shader : " << infolog << std::endl;
		}

	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(object, 1024, NULL, infolog);
				std::cout << "eroare de linkare program : " << infolog << std::endl;
			}
	}
}
Shader::~Shader()
{
	//glDeleteProgram(this->Program);
}
