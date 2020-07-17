/*
* Header file of sprite.h ,this is n interface of class Sprite
*
* This code is part of Tatris game
*
* PURPOSE:
* To generate a sprite randerer
*/



#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "TEXTURE.h"


class Sprite
{
public:
	//Init the sprite to NULL
	Sprite();

	//Init sprite 
	//param a Shader 
	Sprite(Shader &shader);

	Shader getShader();
	//Randers sptite 
	//1 param is texture of sprite 
	//2nd param is position of srite 
	//3rd param is size of sprite 
	//4th param ratation 
	//5th param color of sprite in int
	virtual void randerSprite(Texture &texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec4 color);

	//Destructor
	~Sprite();
private:
	Shader shader;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	void initRanderData();
	
};
#endif // !SRITE_H


