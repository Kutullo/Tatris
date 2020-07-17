/*
* Header file of Shape.h ,this is n interface of class Shape
*
* This code is part of Tatris game
*
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "TEXTURE.h"
#include "sprite.h"




class Shape
{
public:
	//Constructor
	Shape();

	//Constructor
	Shape(int w, int h);

	void genShape(float x, float y, int newshape, glm::vec4 newColor);
	//Rotates the shape 90 deg 
	void rotateShape();

	glm::vec2  tatrio[4];

	int getCellWidth() ;
	int getCellHeight();
	glm::vec4 getColor();
	
	void setColor(glm::vec4 color);
	void setAccelerate ( bool a);

	bool getAccelerate();
	//moves shape downwards
	Shape operator--();
	//move vertically
	void move(glm::vec2 dir);

	//Destructor
	~Shape();

private:
	
	glm::vec2 pos;
	glm::vec4 shapeColor;	
	int unit_width;
	int unit_height;
	int shape;
	float velocity;
	bool accelerate;
};

#endif // !1




