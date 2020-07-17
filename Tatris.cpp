
#include "Tatris.h"


ParticleGenerator * particle[14];

Tatris::Tatris()
{	
	width = 0;
	height = 0;
	tileSize = glm::vec2(280, 400);
	tilPos = glm::vec2(35, 40);
}


Tatris::Tatris(int w, int h)
	:width(w), height(h)
{
	nextShape = Shape(10, 10);
	tileSize = glm::vec2(280, 400);
	tilPos = glm::vec2(20, 100);
	
	tile.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		std::vector<GameObject> newTile;
		tile.reserve(14);
		for (int j = 0; j < 14; j++)
		{
			newTile.emplace_back(GameObject());
		}
		std::cout << endl;
		tile.emplace_back(newTile);
    }

	//Init game resources 
	addShapeColor();
	iniResources();

	//init the first shape
	nextShapeIndex = rand() % 4;
	indexColor = rand() % 6;
	shape.genShape(140, 480., nextShapeIndex, shapeColor[indexColor]);

	//next shape
	nextShapeIndex = rand() % 4;
	indexColor = rand() % 6;
	nextShape.genShape(315, 430., nextShapeIndex, shapeColor[indexColor]);
	
}

void Tatris::iniResources()
{
	//Store textures
	ResourceManager::loadTexture("textures/images11.png", "brick");
	ResourceManager::loadTexture("textures/solid1.png", "grid");
	ResourceManager::loadTexture("textures/wrapper.jpg", "gridwrapper");
	ResourceManager::loadTexture("textures/solid.png", "solid");
	ResourceManager::loadTexture("textures/siderbar.png", "sidebar");
	ResourceManager::loadTexture("textures/logo.png", "logo");
	
	//Store shaders
	ResourceManager::loadShader("shaders/text.vs", "shaders/text.frag", "textShader");	
	ResourceManager::loadShader("shaders/particles.vs", "shaders/particles.frag", "particle");

	//Game fonts
	ResourceManager::loadText("fonts/impact.ttf", 19, "Text1");
	ResourceManager::loadText("fonts/impact.ttf", 16, "Text2");
	ResourceManager::loadText("fonts/impact.ttf", 13, "Text3");
	
	//Init article effect
	for (int i = 0; i < 14; i++)
	{ 
	particle[i] = new ParticleGenerator(
		ResourceManager::getShader("particle"),
		ResourceManager::getTexture("brick"),
		40);
	}
};

void Tatris::logic(float dt)

{
	//gameOver
	for (GameObject LastRow :tile[19])
	{
		if (LastRow.solid == true)
			state = GameOver;
	}

	if (collusion(shape,glm::vec2(0, -1)))
	{
		addShape();
		
	}
	else
	{
		--shape;		
	}
	
	removeSolidRows();

	for (int i = 0; i < 14; i++)
	  particle[i]->update(dt);
}

bool Tatris::collusion(Shape newShape ,glm::vec2 dir)
{
	//Walls 
	//Horizontal boundry
	if (dir == glm::vec2(1, 0) || dir == glm::vec2(-1, 0) || dir == glm::vec2(0, 0))
	{
		for (int i = 0; i < 4; i++)
		{
			float x = newShape.tatrio[i].x + (dir.x*newShape.getCellWidth());			
			if (x < tilPos.x ||x >= (tilPos.x + tileSize.x))
				return true;
		}
	}
		
     //Vertical boundry
	if (dir== glm::vec2(0,-1))
	{
		for (int i = 0; i < 4; i++)
		{
			if (newShape.tatrio[i].y <= tilPos.y)
				return true;
		}
	}
		
	//For tatrio blocks
	for (int i = 0; i < 4; i++)
	{
		int tileIndexX = round((newShape.tatrio[i].x - tilPos.x) / newShape.getCellWidth());
		int indexY = round((newShape.tatrio[i].y - tilPos.y) / newShape.getCellHeight());

		if ( (tileIndexX >= 0 && tileIndexX < tile[0].size())  && (indexY >= 0 && indexY < tile.size()) )
		{
			if (dir == glm::vec2(1, 0) || dir == glm::vec2(-1, 0))
			{
				tileIndexX += dir.x ;
				//TODO boundries when adding x to thr index
				if (tile[indexY][tileIndexX].solid == true)  //vector problem
					return true;
			}
			else if (dir == glm::vec2(0, 1) || dir == glm::vec2(0, -1))
			{
				int y = round(newShape.tatrio[i].y);
				if (y % newShape.getCellHeight() == 0 && indexY>0)
					indexY += dir.y;
					if (tile[indexY][tileIndexX].solid == true)
						return true;		
			}
		}

	}
	return false;

}


void Tatris::addShape()
{
	for (int i = 0; i < 4; i++)
	{
		int indexX =round( (shape.tatrio[i].x - tilPos.x) / shape.getCellWidth());
		int indexY = round((shape.tatrio[i].y - tilPos.y) / shape.getCellHeight());
				
		if ((indexX >= 0 && indexX < tile[0].size()) && (indexY >= 0 && indexY < tile.size()))
		{
			tile[indexY][indexX].solid = true;
			tile[indexY][indexX].color = shape.getColor();
			tile[indexY][indexX].pos = glm::vec2(round(shape.tatrio[i].x), round(shape.tatrio[i].y));			
		}	
	}

	//Add next shape 		
	shape.genShape(140, 480., nextShapeIndex, shapeColor[indexColor]);
	nextShapeIndex = rand() % 4;
	indexColor = rand() % 6;

	//update next shape
	nextShape.genShape(315, 430., nextShapeIndex, shapeColor[indexColor]);	
}

void Tatris::addShapeColor()
{
	shapeColor[0] = glm::vec4(1.0, 1.0, 0.0, 1.0);  //yellow
	shapeColor[1] = glm::vec4(0.0, 0.9, 1.0, 1.0);   //terquise
	shapeColor[2] = glm::vec4(0.3, 0.9, 0.1, 1.0);    //olive
	shapeColor[3] = glm::vec4(1.0, 0.0, 0.0, 1.0);  //red
	shapeColor[4] = glm::vec4(1.0, 0.5, 0.0, 1.0);   //orange
	shapeColor[5] = glm::vec4(1.0, 0.0, 0.9, 1.0);   // purple
}

void Tatris::removeSolidRows()
{
	std::vector<int> index;

	//Check and count solid rows
	for (int i = 0; i < tile.size(); i++)
	{
		int count = 0;
		for (int j = 0; j < tile[0].size(); j++)
		{
			if (tile[i][j].solid == true)
			{
				count ++;
			}
			if (count == tile[0].size())
			{
				index.push_back(i);
				score += 10;
				line++;
				for (int j = 0; j < 14; j++)
					particle[j]->respawnParticle(tile[i][j]);
			}			
		}
	}

	int rowAdded=0;
	for (int i = 0; i < tile.size(); i++)
	{
		for (int row : index)
		{
			if (row == i)
				rowAdded++;
		}

		for (int j = 0; j < tile[0].size(); j++)
		{
			if (rowAdded< tile.size())
			{			
				tile[i][j] = tile[rowAdded][j];
			}
			else
			{
				tile[i][j] = GameObject();
			}
		}
		rowAdded++;
	}


	//Reposition
	for (int i = 0; i < tile.size(); i++)
	{
		for (int j = 0; j < tile[0].size(); j++)
		{
			int x = tilPos.x + j*shape.getCellWidth();
			int y = tilPos.y + i*shape.getCellHeight();
			tile[i][j].pos = glm::vec2(x, y);
		}
	}
	
}

void Tatris::rander(Sprite &sprite)
{
	glm::vec2 size = glm::vec2(shape.getCellWidth(), shape.getCellHeight());

	//side-bar position
	int x = tilPos.x + tileSize.x + 5;
	int y = tilPos.y + 100;
	
	sprite.randerSprite(ResourceManager::getTexture("sidebar"), glm::vec2(x, y), glm::vec2(53, 273), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));

	//Highlighters for values "score ,levelValue ,
	sprite.randerSprite(ResourceManager::getTexture("solid"), glm::vec2(142, 530), glm::vec2(50, 25), 0.0f, glm::vec4(0.0, 0.0, 0.0, 0.4));
	sprite.randerSprite(ResourceManager::getTexture("solid"), glm::vec2(x+12, 303), glm::vec2(30, 20), 0.0f, glm::vec4(0.0, 0.0, 0.0, 0.4));
	sprite.randerSprite(ResourceManager::getTexture("solid"), glm::vec2(x + 12, 255), glm::vec2(30, 20), 0.0f, glm::vec4(0.0, 0.0, 0.0, 0.4));

	//Rander Game Texts and values
	ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"),to_string(score),
		155, 535, 1.0, glm::vec3(0.0, 1.0, 1.0));
	ResourceManager::getText("Text3").RenderText(ResourceManager::getShader("textShader"), "NEXT",
		x+13, 480, 1.0, glm::vec3(1.0, 1.0, 0.0));
	ResourceManager::getText("Text2").RenderText(ResourceManager::getShader("textShader"), "LEVEL",
		x + 8,330, 1.0, glm::vec3(1.0, 1.0, 1.0));
	ResourceManager::getText("Text3").RenderText(ResourceManager::getShader("textShader"), "1",
		x + 20, 308, 1.0, glm::vec3(1.0, 1.0, 1.0));

	ResourceManager::getText("Text2").RenderText(ResourceManager::getShader("textShader"), "LINES",
		x + 8, 282, 1.0, glm::vec3(1.0, 1.0, 1.0));
	ResourceManager::getText("Text3").RenderText(ResourceManager::getShader("textShader"), to_string(line),
		x + 19, 260, 1.0, glm::vec3(1.0, 1.0, 1.0));
	
	sprite.randerSprite(ResourceManager::getTexture("logo"), glm::vec2(5,590), glm::vec2(150, 45), 0.0f, glm::vec4(1.0, 1.0, 1.0, 0.6));
	//Rander the grids background 
	sprite.randerSprite(ResourceManager::getTexture("gridwrapper"), glm::vec2(tilPos.x-3, tilPos.y-3), 
		glm::vec2(tileSize.x + 5, tileSize.y + 5), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));
	
	//Rander the grids
	 for (int i = 0; i < tile.size(); i++)
	  { 
		 for (int j = 0; j < tile[0].size(); j++)
		 {		
				//randers grid cells
				 int x = tilPos.x + j*shape.getCellWidth();
				 int y = tilPos.y + i*shape.getCellHeight();
				 sprite.randerSprite(ResourceManager::getTexture("grid"), glm::vec2(x, y), size, 0.0f, glm::vec4(0.3, 0.2, 0.6, 1.0));

				 //Rander solid shapes on grid
				 if (tile[i][j].solid == true)
				 {
					 sprite.randerSprite(ResourceManager::getTexture("brick"), tile[i][j].pos, size, 0.0f, tile[i][j].color);
				 }		 
		 }	
	 }

	 //dispays the shape
	 for (int i = 0; i < 4; i++)
	 {
		 glm::vec2 pos = glm::vec2(shape.tatrio[i].x, shape.tatrio[i].y);
		 glm::vec4 color = shape.getColor();
		 sprite.randerSprite(ResourceManager::getTexture("brick"), pos, size, 0.0f, color);
	 }

	 //Rander the particle effect
	 for (int i = 0; i < 14; i++)
	   particle[i]->draw();


	 for (int i = 0; i < 4; i++)
	 {
		 glm::vec2 pos = glm::vec2(nextShape.tatrio[i].x, nextShape.tatrio[i].y);
		 glm::vec4 color = nextShape.getColor();
		 size = glm::vec2(nextShape.getCellWidth(), nextShape.getCellHeight());
		 sprite.randerSprite(ResourceManager::getTexture("brick"), pos, size, 0.0f, color);
	 }
	
}

void Tatris::randerTest(Sprite &sprite)
{
	
}


void Tatris::inputs(GLFWwindow *window)
{
	if (state == Menu || state==GameOver)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			state = PlayGame;
		}
	}

	if (state ==PlayGame )
	{ 
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS )
		{
			if (!pressed)
			{
				Shape tempShape=shape;

				if (!collusion(tempShape, glm::vec2(0,-1)))
					shape.rotateShape();
				pressed = true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS )
		{	
			if (!pressed)
			{
				shape.setAccelerate(true);	
			}
		}

		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{		
			if (!pressed && !collusion(shape,glm::vec2(1, 0)))
				{
					shape.move(glm::vec2(1, 0)); 
					pressed = true;
				}
		}		
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS )
		 {
			if (!pressed && !collusion(shape,glm::vec2(-1, 0)))
				 {
					 shape.move(glm::vec2(-1, 0));
					 pressed = true;
				 }		 
		 }
		 else
			 pressed = false;

		 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
			 shape.setAccelerate(false);
	}


}

Tatris::~Tatris()
{
	//delete [] particle;
}
