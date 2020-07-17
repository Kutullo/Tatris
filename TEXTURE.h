/*
* Header file of TEXTURE.h ,this is n interface of class Texture
*
* This code is part of Tatris game
*
* PURPOSE:
* This is a Texture Object .That is generated from file
*/


#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <src\SOIL2.h>
#include <string>

class Texture
{
public:
	Texture();
	//Generates a texture from path 
	//@param path of the texture as string type
	Texture(std::string path);

	//loads images from file 
	//checks errors and generates texture id
	bool loadImage();
	//Binds corresponding texture for use
	void Bind();

private:
	GLuint texture0;
	int height, width;
	unsigned char * image;


};





#endif