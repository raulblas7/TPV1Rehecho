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

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 120;
const uint BALLOON_RATE = 2000;
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
	int flechas = 0;
	Texture* textures[NUM_TEXTURES];
	vector<Arrow*> arrows;
	vector<Balloon*> balloons;
	Bow* arco = nullptr;
	void generateBalloons();
	ImagenesAtributos imags[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},{"..\\images\\Bow2.png", 1, 1},{"..\\images\\balloons.png", 7, 6},{"..\\images\\Bow1.png", 1, 1},{"..\\images\\Arrow1.png",1,1},{"..\\images\\Arrow2.png",1,1},{"..\\images\\digits1.png",1,10} };
	uint frameBalloonTime;
public:
	Game();
	~Game();
	void run();
	void update();
	void render() const;
	void handleEvents();
	bool OnCollision(Balloon* balloon);
	void ThrowArrow();
};

