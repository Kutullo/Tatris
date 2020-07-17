#ifndef TATRIS_H
#define TATRIS_H


// Tat.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib> 
#include "Shape.h"
#include "sprite.h"
#include <vector>
#include <cmath>
#include "TEXTURE.h"
#include <map>
#include "ResourceManager.h"
#include "ParticleGenerator.h"


using namespace std;

#ifndef TILECELL_H
#define TILECELL_H

struct GameObject
{
	bool solid = false;
	bool destroy = false;
	glm::vec2 pos;
	glm::vec4 color;
	
	GameObject() :solid(false), destroy(false), pos(glm::vec2(0, 0)),
		color(glm::vec4(1.0, 1.0, 0.0, 0.0))
	{
		
	};
};
#endif

enum GameState { Menu, PlayGame, quite ,GameOver};

class Tatris
{
public:
	//Init 
	Tatris();

	//Init the game's screen width and height
	Tatris(int w, int h);

	//Initializes the resources to be used by Tatris
	// Init the ResourceManager's Objects
	// e.g resource::Texture ,resource::Shader 
	void iniResources();
	
	void inputs(GLFWwindow *window);
	
	void logic(float dt);

	void rander(Sprite &sprite);

	void setState(GameState newState)  { state = newState;};

	//returns the shape  
	Shape getShape()const;
	int getScore() const;
	GameState getState() const { return state; };



	void removeSolidRows();
	void AddTileRow();
	
	void randerTest(Sprite &sprite);

	void addShape();
	void addShapeColor();
	//collusion with reference to the direction 
	bool collusion(Shape newShape ,glm::vec2 dir);
	virtual ~Tatris();
private:

	Shape shape;
	Shape nextShape;
	std::vector<std::vector<GameObject>> tile;
	int width;
	int height;
	glm::vec2 tileSize;
	glm::vec2 tilPos;
	GameState state =Menu;
	bool pressed=false;	
	int nextShapeIndex;
	int score;
	int line;

	glm::vec4 shapeColor[6];
	int indexColor;
};

#endif // !TATRIS_H
