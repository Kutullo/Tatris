#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Shader.h"
#include "Texture.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Text.h"

class ResourceManager
{
public:

	//Resource storage 
	static std::map <std::string, Shader > shaders;
	static std::map <std::string, Texture> textures;
	static std::map<std::string, Text> texts;

	//Loads shader from file
	static Shader loadShader(const GLchar* vShader, const GLchar* fShader,std::string );
	//Gets stored shader 
	static Shader getShader(std::string name);
	//Loads texture from file
	static Texture loadTexture(const GLchar* file, std::string name);
	//Gets stored texture
	static Texture getTexture(std::string name);
	//loads text from font file and stores chr set
	static Text loadText(std::string fontname, GLuint size, std::string name);

	//Loads font 
	static Text getText(std::string name);

	//deletes the loaded data
	static void Clear();

private:
	ResourceManager(){};
	static Shader loadShaderFromFile(const GLchar* vShader, const GLchar* fShader);
	static Texture loadTextureFromFile(const GLchar*file);
	static Text loadTextFromFile(std::string fontname,GLuint size);

};





#endif