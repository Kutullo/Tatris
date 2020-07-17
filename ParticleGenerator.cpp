#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator()
{
}

ParticleGenerator::ParticleGenerator(Shader newShader, Texture newTexture, int newAmount)
	:shader(newShader), texture(newTexture), amount(newAmount) 
{
	init();

}

void ParticleGenerator::init()
{

	
	GLuint VBO;

	GLfloat particleQuad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	//Create particle instances
	particle.reserve(amount);
	for (int i = 0; i < amount; i++)
		particle.emplace_back(Particle());
}



void ParticleGenerator::update(GLfloat dt )
{
	
	   //Updating every particle
	for (int i = 0; i < amount; i++)
	{
		
		particle[i].Life -= 0.0001; // reduce life
		if (particle[i].Life > 0.0f)
		{ // particle is alive, thus update
			particle[i].Position.y -= particle[i].Velocity *dt;
			particle[i].Color.a -= 0.2*dt;
		}
	}
	
}


void ParticleGenerator::respawnParticle(GameObject &tatrisBlock)
{
		
	for (int i = 0; i < amount; i++)
	{
		GLfloat random = ((rand() % 100) - 50) / 5.0f;
		GLfloat randPosX = ((rand() % 100) - 50) / 5.0f + 10;
		GLfloat randPosY = ((rand() % 100) - 50) / 5.0f + 10;
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);

		//particle.Position = shape.tatrio[0] + random + offset;
		particle[i].Position = glm::vec2(tatrisBlock.pos.x + randPosX, tatrisBlock.pos.y + randPosY);

		//particle.Color = shape.getColor();
		particle[i].Color = tatrisBlock.color;
		particle[i].Life = 1.0f;
		particle[i].Velocity =15;
	}
	
}


ParticleGenerator::~ParticleGenerator()
{
	
}

// Render all particles
void ParticleGenerator::draw()
{
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.Use();
	if (particle[1].Life >0)
	
	for (Particle particle : particle)
	{
		if (particle.Life > 0.0f)
		{

			glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(360), 0.0f, static_cast<GLfloat>(640), -1.0f, 1.0f);
			glUniformMatrix4fv(glGetUniformLocation(shader.shaderprogram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniform2f(glGetUniformLocation(shader.shaderprogram, "offset"), particle.Position.x, particle.Position.y);

			glUniform4f(glGetUniformLocation(shader.shaderprogram, "color"),
				particle.Color.r, particle.Color.g, particle.Color.b, particle.Color.a);

			//this->texture.Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
