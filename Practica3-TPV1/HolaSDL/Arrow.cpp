#include "Arrow.h"
#include "PlayState.h"

Arrow::Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, GameState* state_)
	: ArrowsGameObject(pos_, vel_,width_, height_,arrow_, state_)
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
		dynamic_cast<PlayState*>(state)->killObject(it);
		
	}
}

int Arrow::getNHits()
{
	return numHits;
}

void Arrow::saveToFile(ofstream& output) {
	output << "Flecha" << endl;
	ArrowsGameObject::saveToFile(output);
}

void Arrow::loadFromFile(ifstream& input) {
	ArrowsGameObject::loadFromFile(input);
}
