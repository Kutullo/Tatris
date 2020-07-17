/*
* Impementation file  sprite.cpp ,of class Sprite
*
* This code is part of Tatris game
*/


#include "sprite.h"


Sprite::Sprite()
{

}



Sprite::Sprite(Shader &newShader)
{
	shader = newShader;
    initRanderData();
}

void Sprite::initRanderData()
{


	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f // Top Left
	}; 


	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &EBO);

	//Bind the vao before the vbo
	glBindVertexArray(VAO);

	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind the VAO

	glBindVertexArray(0);

}

Shader Sprite::getShader()
{
	return shader;
}
 void Sprite::randerSprite(Texture &texture, glm::vec2 pos,glm::vec2 size,float rotate, glm::vec4 color)
{

	 shader.Use();

	 glm::mat4 model(1.0);
	 // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	 model = glm::translate(model, glm::vec3(pos, 0.0f)); 

	 model = glm::translate(model, glm::vec3(1.0f * size.x, 1.0f * size.y, 0.0f)); // Move origin of rotation to center of quad
	 model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	 model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	 model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale 

	 //Set Model matrix on shader
	 glUniformMatrix4fv(glGetUniformLocation(shader.shaderprogram,"model"), 1, GL_FALSE, glm::value_ptr(model));

	 //Set color 
	 glUniform4f(glGetUniformLocation(shader.shaderprogram, "textureColor"), color.r, color.g, color.b,color.a);
	 
	 texture.Bind();
	 glBindVertexArray(this->VAO);

	 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	 glBindVertexArray(0);

}


Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &this->VAO);
}