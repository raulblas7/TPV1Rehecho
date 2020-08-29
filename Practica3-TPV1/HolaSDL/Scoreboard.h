#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <vector>
#include "GameObject.h"

using namespace std;

const int MAX_ARROW_TEXTURES = 10;
class Game;
class Scoreboard:public GameObject
{
private:
	Point2D esqIzq = Point2D(0, 0);
	Texture* points = nullptr;
	Texture* arrows = nullptr;
	uint ancho = 0;
	uint alto = 0; 
	Game* game = nullptr;
	vector<int>digitos;

public:
	Scoreboard();
	Scoreboard(Point2D esqIzq, uint ancho, uint alto, Texture* points, Texture* arrows,Game*game);
	void Puntuacion(int score);
	void render();
	void update() {};

};

