#include "ArrowsGameObject.h"
#include <fstream>
void ArrowsGameObject::render()
{
	SDLGameObject::render();
}

void ArrowsGameObject::update()
{
	pos = pos + vel;
}


void ArrowsGameObject::saveToFile(ofstream& output)
{
	output << pos.getX() << endl;
	output << pos.getY() << endl;
	output << vel.getX() << endl;
	output << vel.getY() << endl;
	output << width << endl;
	output << height << endl;
}
void ArrowsGameObject::loadFromFile(ifstream& input)
{
	double x, y, velX, velY;
	input >> x;
	input >> y;
	pos = Point2D(x, y);
	input >> velX;
	input >> velY;
	vel = Vector2D(velX, velY);
	input >> width;
	input >> height;
}
