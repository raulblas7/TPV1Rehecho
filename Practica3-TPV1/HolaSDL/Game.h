#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Bow.h"
#include <vector>
#include "Scoreboard.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 60;
const uint BALLOON_RATE = 2000;
const int POINT_ADD = 10;

struct ImagenesAtributos {
	string filename;
	uint nRows, nCols;
};
class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	int points = 0;
	int flechas = 5;
	Texture* textures[NUM_TEXTURES];
	vector<Arrow*> arrows;
	vector<Balloon*> balloons;
	Bow* arco ;
	Scoreboard* scoreboard;
	void generateBalloons();
	ImagenesAtributos imags[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},{"..\\images\\Bow2.png", 1, 1},{"..\\images\\balloons.png", 7, 6},{"..\\images\\Bow1.png", 1, 1},{"..\\images\\Arrow1.png",1,1},{"..\\images\\Arrow2.png",1,1},{"..\\images\\digits1.png",1,10} };
	uint frameBalloonTime;
	list<GameObject*> objects;
	list<Arrow*> arrows;
	list<EventHandler*> events;
	list<GameObject*> objectsToDelete;
public:
	Game();
	~Game();
	void run();
	void update();
	void render() ;
	void handleEvents();
	bool OnCollision(Balloon* balloon);
	void ThrowArrow(Point2D pos);
	void AddPoints();
	void killObject(list<GameObject*>::iterator i);
	int GetNumberArrows() { return flechas; };
};

