/*
* Implimantation file TEXTURE.cpp ,this is impimentation of class TEXTURE
*
* This code is part of Tatris game
*/


#include "TEXTURE.h"


Texture::Texture() 
	:texture0(-1), height(0), width(0), image(nullptr)
{

}

Texture::Texture(std::string path)
{
	image= SOIL_load_image(path.c_str(), &width, &height, 0,SOIL_LOAD_RGBA);

	loadImage();	
}

bool Texture::loadImage()
{
 glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (image)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE,image);
		glGenerateMipmap(GL_TEXTURE_2D);

		
	}
	else
	{
		std::cout << "ERROR ::LOAD::TEXTURE::FAILED";
		return false;

	}

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); 

	return true;

}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texture0);
}