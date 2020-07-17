#include "ResourceManager.h"

 std::map <std::string, Texture> ResourceManager::textures;
 std::map <std::string, Shader > ResourceManager::shaders;
  std::map<std::string, Text> ResourceManager::texts;

 

 Shader ResourceManager::loadShader(const GLchar* vShader, const GLchar* fShader, std::string name)
 {
	 shaders[name] = loadShaderFromFile(vShader, fShader);
	 return shaders[name];
 }

 Shader ResourceManager::getShader(std::string name)
 {	
	 return shaders[name];
 }

 Shader ResourceManager::loadShaderFromFile(const GLchar* vShader, const GLchar* fShader)
 {	
	 // 2. Now create shader object from source code
	 Shader shader(vShader, fShader);	 
	 return shader;	
 }


 Texture ResourceManager::loadTexture(const GLchar* file, std::string name)
 {
	 textures[name] = loadTextureFromFile(file);
	 return textures[name];
 }

 Texture ResourceManager::getTexture(std::string name)
 {
	 return textures[name];
 }

 Texture ResourceManager::loadTextureFromFile(const GLchar* file)
 {
	 Texture texture(file);
	 return texture;
 }

 Text ResourceManager::loadText(std::string fontname, GLuint size, std::string name)
 {
	 texts[name] = loadTextFromFile(fontname, size);
	 return texts[name];
 }

 Text ResourceManager::getText(std::string name)
 {
	 return texts[name];
 }

 Text ResourceManager::loadTextFromFile(std::string fontname, GLuint size)
 {
	 Text txt(360,640);
	 txt.load(fontname, size);
	 return txt;
 }

 void ResourceManager::Clear()
 {
	 // (Properly) delete all shaders	
	 for (auto iter : shaders)
		 glDeleteProgram(iter.second.shaderprogram);
	 // (Properly) delete all textures
	// for (auto iter : textures)
		// glDeleteTextures(1, &iter.second.s);
 }