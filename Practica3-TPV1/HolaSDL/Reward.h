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
	int time = 0;
	int timeP = 0;
public:
	Reward(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* reward_, Texture* bubble_, int timePower,GameState* game_);
	~Reward() {};
	void render();
	void update();
	void handleEvent(SDL_Event& event);
	void saveToFile(ofstream& output);
	void loadFromFile(ifstream& input);
	virtual void accion(bool active) = 0;
};

