//Particle interfacefor the TATRIS Game
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "TEXTURE.h"
#include "Shape.h"


#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H


struct Particle {
	glm::vec2 Position;
	GLfloat Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


#ifndef TILECELL_H
#define TILECELL_H
struct GameObject
{
	bool solid = false;
	bool destroy = false;
	glm::vec2 pos;
	glm::vec4 color;

	//Constructor
	GameObject() :solid(false), destroy(false), pos(glm::vec2(0, 0)),
		color(glm::vec4(1.0, 1.0, 0.0, 0.0))
	{
	};
};
#endif


class ParticleGenerator
{
public:
	//Constructor
	ParticleGenerator();

	ParticleGenerator(Shader newShader, Texture newTexture, int newAmount);
		
	//Randers the particles
	void draw();

	// Update all particles
	void update(GLfloat dt );

	//
	void respawnParticle(GameObject& tatrisBlock);

	//Destructor
	~ParticleGenerator();

private:

	std::vector<Particle> particle;
	Shader shader;
	Texture texture;
	int amount;
	GLuint  VAO;

	//intializes the buffers for game 
	void init();
	


	
};
#endif // !PARTICLEGENERATOR_H


