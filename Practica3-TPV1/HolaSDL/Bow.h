#pragma once
#include "Arrow.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"

class Game;
class Bow:public ArrowsGameObject, public EventHandler
{
private:
	Texture* bowC;
	Texture* aux;
	bool cargado = false;
	bool mov = false;


public:
	Bow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* bow_ ,Texture* bowC_, Game* game_);
	~Bow() {};
	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& event);


	/*virtual void render();
	virtual void update();
	//virtual ~Bow() {};
	virtual void handleEvent(SDL_Event& event);
	// ~Bow() {};
	void loadFromFile(ifstream& input);
	void saveToFile(ofstream& outuput);*/
};

