
/*
* Implimantation file Shader.cpp ,this is impimentation of class Shader
*
* This code is part of Tatris game
*/


#include "Shader.h"


Shader::Shader()
{
	shaderprogram = NULL;
}

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	std::ifstream Vin(vertexSourcePath, std::ios::in), fin;
	GLuint vertexShader, fragmentShader;
	std::string vShaderSource;
	std::string fShaderSource;

	//load files 
		//Vin.open(vertexSourcePath);	
		if (Vin.fail())
			std::cout << "ERROR::SHADER::VERTEX::LOAD_FILE_FAILED\n";
	
		fin.open(fragmentSourcePath);
		if (fin.fail())
		std::cout << "ERROR::SHADER::FRAGMENT::LOAD_FILE_FAILED\n";

   // loading dtring from source
		std::string line;
		while (!Vin.eof())
		{
			std::getline(Vin, line);
			vShaderSource.append(line + "\n");
			
		}

	
		Vin.close();

		while (!fin.eof())
		{
			std::getline(fin, line);
			fShaderSource.append(line + "\n");
			
		}

	
	fin.close();

	

//	std::cout << vShaderSource << "\n";
	//std::cout << fShaderSource << "\n";
	const GLchar * vShaderCode = vShaderSource.c_str();
	const GLchar * fShaderCoder = fShaderSource.c_str();

	//cOMPILING THE SHADER_p
//..............


	GLint success;
	GLchar infoLog[512];
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
			<< std::endl;
	};

	// FRAGMENT 

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCoder, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
			<< std::endl;
	};

	// cREATING PROGRAM 
	this->shaderprogram = glCreateProgram();
	glAttachShader(this->shaderprogram, vertexShader);
	glAttachShader(this->shaderprogram, fragmentShader);
	glLinkProgram(this->shaderprogram);

	glGetProgramiv(this->shaderprogram, GL_LINK_STATUS, &success);

	if (!success)
	{
		{
			glGetProgramInfoLog(this->shaderprogram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog <<
				std::endl;
		}
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Use()
{
	glUseProgram(this->shaderprogram);
}