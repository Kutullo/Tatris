/*
* Header file of Shader.h ,this is n interface of class Shader 
* 
* This code is part of Tatris game 
*
* PURPOSE:
* This is a shader Object .That is generated from file 
*/



#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



class Shader
{
public:
	GLuint shaderprogram;
	//Constructor 
	Shader();
	//Compiles and  genrerates  shader program from source
	//1 @param char * of vertex path 
	//2 @param char * of fragment path 
	Shader( const GLchar* vertexSourcePath ,const GLchar* fragmentSourcePath);
	//sets shader active
	void Use();
	

private:
	
	


};









#endif // !SHADER_H
