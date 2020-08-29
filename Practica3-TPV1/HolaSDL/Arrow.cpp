#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, Game* game_)
	: ArrowsGameObject(pos_, vel_,width_, height_,arrow_, game_)
{
}


void Arrow::render() 
{
	ArrowsGameObject::render();
}

void Arrow::update()
{
	ArrowsGameObject::update();
	if (pos.getX() >= 800) {
		game->killObject(it);
	}
}

int Arrow::getNHits()
{
	return numHits;
}

void Arrow::loadFromFile(ifstream& input)
{
}

void Arrow::saveToFile(ofstream& outuput)
{
}
