#pragma once
# include <GL/glew.h>
# include <glm.hpp>
# include <type_ptr.hpp>
# include <string>
# include <iostream>
class Shader
{
public:
	GLuint Program;
	void use();
	Shader();
	void Compile(const GLchar *vertex,const GLchar *fragment,const GLchar *geometry=nullptr);
	void SetFloat(const GLchar* nume, GLfloat x, GLboolean useShade );
	void SetInteger(const GLchar* nume, GLint x, GLboolean useShader );
	void SetVec2f(const GLchar* nume, GLfloat x, GLfloat y, GLboolean useShader);
	void SetVec2f(const GLchar* nume,const glm::vec2 &value, GLboolean useShader );
	void SetVec3f(const GLchar* nume, GLfloat x , GLfloat y, GLfloat z, GLboolean useShader);
	void SetVec3f(const GLchar* nume,const glm::vec3 &value, GLboolean useShader );
	void SetVec4f(const GLchar* nume, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader);
	void SetVec4f(const GLchar *nume, const glm::vec4 &value, GLboolean useShader);
	void SetMatrix4(const GLchar* nume,const glm::mat4 &value, GLboolean useShader);
	void CeckCompileErrors(GLuint object, std::string type);
	~Shader();
};

