#pragma once
#include "GameState.h"
#include "Bow.h"
#include "Scoreboard.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "Arrow.h"
#include <list>
#include "Butterfly.h"
#include "Reward.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "GiveMeArrows.h"
#include "BigArrows.h"
#include <math.h>
#include "Balloon.h"
#include "SDLApplication.h"


const uint NUM_Lvl = 6;
const int POINT_ADD = 10;
const int POINT_LESS = 5;
const uint BALLOON_RATE = 2000;

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
	
class MenuButton;

class PlayState: public GameState
{
private:
	int points = 0;
	int flechas = 0;
	int mariposas = 0;
	MinMaxValue Vel_Bal;
	MinMaxValue Vel_But;
	int level = -1;
	uint frameBalloonTime;
	int arrowsSize = 0;
	Bow* arco;
	Scoreboard* scoreboard;
	bool cargar = false;
	Texture* fondo = nullptr;
	Lvl niveles[NUM_Lvl] = {
	{"..\\images\\bg1.png", 10, 3, 0,5,2,4},
	{"..\\images\\bg_spring_trees_1.png", 11, 4,1,5,2,4},
	{"..\\images\\Cartoon_Forest_BG_01.png", 12, 8,2,5,2,4},
	{"..\\images\\Cartoon_Forest_BG_02.png", 13, 12,3,6,2,4},
	{"..\\images\\Cartoon_Forest_BG_03.png", 14, 15,3,7,2,4},
	{"..\\images\\Cartoon_Forest_BG_04.png", 15, 20,3,8,2,4}
	};
	
	list<Arrow*> arrows;
	list<GameObject*> objectsToDelete;
	MenuButton* pauseButton=nullptr;
public:
	PlayState(SDLApplication* game, bool cargar);
	~PlayState();
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
	 virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event& e);
};

