#pragma once
#include"Texture.h"
#include"Shader.h"
# include <string>
# include <fstream>
# include <iostream>
# include <sstream>
# include <map>
#include<SOIL.h>



class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;
	static Shader LoadShader(const GLchar *vertexFile, const GLchar *fragmentFile,std::string name, const GLchar *geometryFile=nullptr);
	static Shader GetShader(std::string name);
	static Texture LoadTexture(const GLchar *textureFile, GLboolean alpha, std::string name);
	static Texture GetTexture(std::string name);
	void clear();
	ResourceManager();
	~ResourceManager();
public:
	static Shader LoadFromFile(const GLchar *vFile, const GLchar * fFile, const GLchar *gFile = nullptr);
	static Texture LoadTextureFromFile(const GLchar *tFile, GLboolean alpha, std::string name);
};

