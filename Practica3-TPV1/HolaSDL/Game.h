#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "Bow.h"
#include "Reward.h"
#include <vector>
#include "Scoreboard.h"
#include "GameObject.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "GiveMeArrows.h"
#include "BigArrows.h"
#include "EventHandler.h"
#include <list>
#include <math.h>

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 9;
const uint FRAME_RATE = 60;
const uint BALLOON_RATE = 2000;
const int POINT_ADD = 10;
const int POINT_LESS = 5;
const uint NUM_Lvl = 6;

struct ImagenesAtributos {
	string filename;
	uint nRows, nCols;
};
struct MinMaxValue
{
	double min;
	double max;

};
struct Lvl
{
	string filename;
	int numFlecha;
	int numMariposas;
	struct MinMaxValue velBal;
	struct MinMaxValue velBut;
};
class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	int points = 0;
	int flechas = 0;
	int mariposas = 0;
	MinMaxValue Vel_Bal;
	MinMaxValue Vel_But;
	int level = - 1;
	uint frameBalloonTime;
	Texture* textures[NUM_TEXTURES];
	Texture* fondo;
	//vector<Arrow*> arrows;
	int arrowsSize = 1;

	vector<Balloon*> balloons;
	Bow* arco ;
	Scoreboard* scoreboard;
	Lvl niveles[NUM_Lvl] = {
	{"..\\images\\bg1.png", 10, 3, 0,5,2,4},
	{"..\\images\\bg_spring_trees_1.png", 11, 4,1,5,2,4},
	{"..\\images\\Cartoon_Forest_BG_01.png", 12, 8,2,5,2,4},
	{"..\\images\\Cartoon_Forest_BG_02.png", 13, 12,3,6,2,4},
	{"..\\images\\Cartoon_Forest_BG_03.png", 14, 15,3,7,2,4},
	{"..\\images\\Cartoon_Forest_BG_04.png", 15, 20,3,8,2,4}
	};
	ImagenesAtributos imags[NUM_TEXTURES] = { {"..\\images\\Bow2.png", 1, 1},{"..\\images\\balloons.png", 7, 6},{"..\\images\\Bow1.png", 1, 1},{"..\\images\\Arrow1.png",1,1},{"..\\images\\Arrow2.png",1,1},{"..\\images\\digits1.png",1,10},{"..\\images\\butterfly2.png",4,10},{"..\\images\\rewards.png",10,8} ,{"..\\images\\bubble.png",1,1} };
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
	bool OnCollision(list<GameObject*>::iterator it);
	void ThrowArrow(Point2D pos);
	void AddPoints(int numhits);
	void LessPoints();
	void CreateReward(Vector2D pos, int num);
	void generateBalloons();
	void generateButterfly();
	void killObject(list<GameObject*>::iterator i);
	int GetNumberArrows() { return flechas; };
	void NewLevel();
	void saveToFile(ofstream& output);
	void loadFroamFile(ifstream& input);
	void ArrowSize(double proporcion);
	void AddArrows(int num);
};

