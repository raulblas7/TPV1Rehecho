#pragma once
#include "GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "EndState.h"
#include "SDLError.h"
#include "checkML.h"

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 15;
const uint FRAME_RATE = 60;



struct ImagenesAtributos {
	string filename;
	uint nRows, nCols;
};
class GameStateMachine;
class SDLApplication
{
private:
	GameStateMachine* gamestamac;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];
	Texture* fondo=nullptr;
	PlayState* play = nullptr;
	PauseState* pause = nullptr;
	EndState* end = nullptr;
	MainMenuState* menu = nullptr;
	ImagenesAtributos imags[NUM_TEXTURES] = { {"..\\images\\Bow2.png", 1, 1},{"..\\images\\balloons.png", 7, 6},{"..\\images\\Bow1.png", 1, 1},{"..\\images\\Arrow1.png",1,1},
		{"..\\images\\Arrow2.png",1,1},{"..\\images\\digits1.png",1,10},{"..\\images\\butterfly2.png",4,10},{"..\\images\\rewards.png",10,8} ,{"..\\images\\bubble.png",1,1}
	,{"..\\images\\play.png",1,1},{"..\\images\\pause.png",1,1},{"..\\images\\load.png",1,1} ,{"..\\images\\home.png",1,1}
	,{"..\\images\\save.png",1,1},{"..\\images\\exit_.png",1,1} };
	
public:
	SDLApplication();
	~SDLApplication();
	void run();
	void update();
	void render() ;
	void handleEvents();
	Texture* GetTexture(int texture) { return textures[texture]; };
	SDL_Renderer* GetRenderer() { return renderer; };
	void Play();
	void Pause();
	void Exit();
	void Load();
	void Save();
	void MainMenu();
	void GameOver();
	void YouWin();
	void ContinuePlaying();
};

