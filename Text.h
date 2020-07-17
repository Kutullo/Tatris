/*
* Header file of Text.h ,this is n interface of class Text
*
* This code is part of Tatris game
*/

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>

#include "Shader.h"
#include "Texture.h"

#ifndef  TEXT_H
#define TEXT_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};



class Text
{
public:
	//Constructor
	Text();
	//Init 
	Text(GLuint width ,GLuint height);
	//Loads the font to be  used
	//1 @param path of font 
	//@ @param size of font 
	void load(string _name ,GLuint fontsize);
	
	// Stores the Textures for the characters
	//Asci characters 128
	std::map<GLchar, Character> Characters;
	

	//Randers text  on current window 
	// Uses text.vs and text.frag for shader 
	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	//Randers a char  on current window 
	// Uses text.vs and text.frag for shader 
	void RenderTextc(Shader &shader, char text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	//Destructor
	~Text();
private:
	GLuint SCR_WIDTH, SCR_HEIGHT;
	GLuint VAO, VBO;
	
};





#endif

