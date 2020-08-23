#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <vector>
using namespace std;

const int MAX_ARROW_TEXTURES = 10;
class Game;
class Scoreboard
{
private:
	Point2D esqIzq = Point2D(0, 0);
	Texture* points = nullptr;
	Texture* arrows = nullptr;
	uint ancho = 0;
	uint alto = 0; 
	vector<int>digitos;
	int numberarrows;



public:
	Scoreboard();
	Scoreboard(Point2D esqIzq, uint ancho, uint alto, Texture* points, Texture* arrows, int numberArrows);
	void Puntuacion(int score);
	void Arrows();
	void render();

};

