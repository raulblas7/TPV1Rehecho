#pragma once
#include "EventHandler.h"
#include "ArrowsGameObject.h"

class Reward:public ArrowsGameObject,public  EventHandler
{
private:
	bool burbuja = true;
	bool tocado = false;
	bool power = false;
	int timePower = 3000;
	Texture* bubble;
	int row;
	int frameAnimation = 0;
	uint time;
public:
	Reward(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* reward_, Texture* bubble_, Game* game_);
	void render();
	void update();
	void handleEvent(SDL_Event& event);
	void saveToFile(ofstream& output);
	void loadFromFile(ifstream& input);
	//virtual void accion(bool active) = 0;

};

