#include "Shape.h"


Shape::Shape()
{
	
	pos = glm::vec2(100, 100);
	shapeColor = glm::vec4(1.0f, 1.0f, 0.0f,1.0f);
	unit_width = 20;
	unit_height = 20;
	shape=0;
	velocity = 0.1;
	accelerate = false;
	
}

Shape::Shape(int w ,int h)
{
	pos = glm::vec2(100, 100);
	shapeColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	unit_width = w;
	unit_height = h;
	shape = 0;
	velocity = 0.1;
	accelerate = false;	
}



void Shape::genShape(float x,float y,int newshape,glm::vec4 newColor)
{
	shape = newshape;

	switch (shape)
	{
	case 0:
		// Horizontal shape		
		tatrio[0].x = x;  tatrio[0].y = y;
		tatrio[1].x = x;  tatrio[1].y =y -unit_height;
		tatrio[2].x = x;  tatrio[2].y =y -2*unit_height;
		tatrio[3].x = x;  tatrio[3].y =y -3*unit_height;		
		break;
	case 1:
		// L shape
		tatrio[0].x = x;		        tatrio[0].y = y;
		tatrio[1].x = x;		        tatrio[1].y = y - unit_height;
		tatrio[2].x = x;				tatrio[2].y = y - 2 * unit_height;
		tatrio[3].x = x + unit_width;	tatrio[3].y = y - 2 *unit_height;
		
		break;
	case 2:
		//f shape
		tatrio[0].x = x;                 tatrio[0].y = y;
		tatrio[1].x = x+unit_width;      tatrio[1].y = y;
		tatrio[2].x = x+unit_width;      tatrio[2].y = y + unit_height;
		tatrio[3].x = x+ 2*unit_width;   tatrio[3].y = y;

		break;
	case 3:
		// z shape
		tatrio[0].x = x;                   tatrio[0].y = y;
		tatrio[1].x = x + unit_width;      tatrio[1].y = y - unit_height;
		tatrio[2].x = x + unit_width;      tatrio[2].y = y;
		tatrio[3].x = x + 2 * unit_width;  tatrio[3].y = y - unit_height;
		break;
	default:
		break;
	}

	shapeColor = newColor;
}


void Shape::rotateShape()
{
	
	int x1, y1;
	int x2, y2;
	int xconst;
	int yconst;

	xconst = tatrio[1].y -tatrio[1].x;
	yconst = tatrio[1].y +tatrio[1].x;

	for (int i = 0; i < 4; i++)
	{
		x1 = tatrio[i].y;
		y1 = -1 * (tatrio[i].x);
		tatrio[i].x = x1 - xconst;
		tatrio[i].y = y1 + yconst;
	}
}

void Shape::move(glm::vec2 dir)
{
	tatrio[0].x = tatrio[0].x + dir.x * unit_width;
	tatrio[1].x = tatrio[1].x + dir.x * unit_width;
	tatrio[2].x = tatrio[2].x + dir.x * unit_width;
	tatrio[3].x = tatrio[3].x + dir.x * unit_width;
}



int Shape::getCellWidth()
{
	return unit_width;
}

int Shape::getCellHeight()
{
	return unit_height;
}
glm::vec4 Shape::getColor()
{
	return shapeColor;
}

void Shape::setColor(glm::vec4 color)
{
	shapeColor = color;
}
void Shape::setAccelerate(bool a)
{
	accelerate = a;
}

bool Shape::getAccelerate()
{
	return accelerate;
}

Shape Shape::operator--()
{
	float a;
	if (accelerate)
		a = 8;
	else
		a = 1;

	tatrio[0].y = tatrio[0].y - velocity * a;
	tatrio[1].y = tatrio[1].y - velocity * a;
	tatrio[2].y = tatrio[2].y - velocity * a;
	tatrio[3].y = tatrio[3].y - velocity * a;
	return Shape();
}


Shape::~Shape()
{
}
