#include "ResourceManager.h"
std::map<std::string, Texture>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vertexFile, const GLchar *fragmentFile, std::string name, const GLchar *geometryFile)
{
	Shaders[name] = LoadFromFile(vertexFile, fragmentFile, geometryFile);
	return Shaders[name];
}
Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}
Texture ResourceManager::LoadTexture(const GLchar *textureFile, GLboolean alpha, std::string name)
{
	Textures[name] = LoadTextureFromFile(textureFile, alpha, name);
	return Textures[name];
}
Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}
void ResourceManager::clear()
{
	for (auto i : Shaders)
		glDeleteProgram(i.second.Program);
	for (auto i : Textures)
		glDeleteTextures(1,&i.second.id);
}
Shader ResourceManager::LoadFromFile(const GLchar *vFile, const GLchar * fFile, const GLchar *gFile)
{
	std::string vertCode;
	std::string fragCode;
	std::string geoCode;
	std::ifstream vfile;
	std::ifstream ffile;
	std::ifstream gfile;
	vfile.exceptions(std::ifstream::badbit);
	ffile.exceptions(std::ifstream::badbit);
	gfile.exceptions(std::ifstream::badbit);
	try
	{
		vfile.open(vFile);
		ffile.open(fFile);
		std::stringstream vertstream,fragstream;
		vertstream << vfile.rdbuf();
		fragstream << ffile.rdbuf();
		vertCode = vertstream.str();
		fragCode = fragstream.str();
		vfile.close();
		ffile.close();
		if (gFile != nullptr)
		{
			gfile.open(gFile);
			std::stringstream gstream;
			gstream << gfile.rdbuf();
			geoCode = gstream.str();
			gfile.close();
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failure la citire"<< std::endl;
	}
	catch (std::exception e)
	{
		std::cout << "eroare la citire" << std::endl;
	}
	const GLchar * vCode = vertCode.c_str();
	const GLchar * fCode = fragCode.c_str();
	const GLchar* gCode = geoCode.c_str();
	if (gFile == nullptr)
		gCode = nullptr;
	Shader shader;
	shader.Compile(vCode, fCode, gCode!=nullptr?gCode:nullptr);	
	return shader;
}
Texture ResourceManager::LoadTextureFromFile(const GLchar *tFile, GLboolean alpha, std::string name)
{
	Texture tex;
	if (alpha)
	{
		tex.Image_format = GL_RGBA;
		tex.Internal_format = GL_RGBA;

	}
	GLint width, height;
	unsigned char *image= SOIL_load_image(tFile, &width, &height, 0, tex.Image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	std::cout << SOIL_last_result();
	tex.generate(width, height, image);
	SOIL_free_image_data(image);
	return tex;
}
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
