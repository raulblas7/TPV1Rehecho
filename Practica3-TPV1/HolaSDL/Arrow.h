#pragma once
#include "ArrowsGameObject.h"

class Arrow:public ArrowsGameObject
{
private:
	 int numHits = 0;
public:
	Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, Game* game_);
	~Arrow() {};
	void render();
	void update();
	int getNHits();
	void AddHit() { numHits++; }
	void loadFromFile(ifstream& input);
	void saveToFile(ofstream& outuput);
};

