#include "Game.h"


Game::Game()
{// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("…", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		//. . .
		textures[i] = new Texture(renderer,imags[i].filename, imags[i].nRows, imags[i].nCols);
	}

	// We finally create the game objects
	arco = new Bow(Point2D(0, WIN_HEIGHT/2), Vector2D(0, 10), 100, 100, textures[3],textures[1],this);
	scoreboard = new Scoreboard(Point2D(300, 0), 25, 35, textures[6], textures[5], flechas);

	//game starts
	run();
}

Game::~Game()
{
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	for (int k = 0; k < arrows.size(); k++) {
		delete arrows[k];
	}
	for (int j = 0; j < balloons.size(); j++) {
			delete balloons[j];		
	}
	
	delete arco;
	delete scoreboard;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	uint frameTime = SDL_GetTicks();
	frameBalloonTime = SDL_GetTicks();
	while (!exit) { // Falta el control de tiempo
		handleEvents();

		if (frameTime+FRAME_RATE<=SDL_GetTicks())
		{
			update();
			frameTime = SDL_GetTicks();
		}

		render();
	}
}
void Game::update() {
	generateBalloons();

	arco->update();
	
		for (int j = 0; j < balloons.size(); j++) {
			if (balloons[j]->update()) {
				delete balloons[j];
				balloons.erase(balloons.begin() + j);
			}
		}
	
	if (!arrows.empty()) {
		for (int k = 0; k < arrows.size(); k++) {
			if (arrows[k]->update()) {
				delete arrows[k];
				arrows.erase(arrows.begin() + k);
			}
		}
	}
}
void Game::render() const {
	SDL_RenderClear(renderer);
	textures[0]->render(SDL_Rect{ 0 ,0, WIN_WIDTH, WIN_HEIGHT }, SDL_FLIP_NONE);
	arco->render();
	if (!arrows.empty()) {
		for (int i = 0; i < arrows.size(); i++) {
			arrows[i]->render();
		}
	}
	if (!balloons.empty()) {
		for (int j = 0; j < balloons.size(); j++) {
			balloons[j]->render();
		}
	}
	//renderizado scoreboard
	scoreboard->render();	
	SDL_RenderPresent(renderer);
}
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		arco->handleEvents(event);
		
	}
}

bool Game::OnCollision(Balloon* balloon)
{
	bool tocado = false;
	for (int i = 0; i < arrows.size(); i++)
	{
		if (SDL_HasIntersection(&balloon->getRect(), &arrows[i]->getRect()))
		{
			AddPoints();
			return true;
		}
	}

	return false;
}

void Game::ThrowArrow(Point2D pos)
{
	if (flechas>0)
	{
		double witdh = 90;
		double height = 20;
		arrows.push_back(new Arrow(Point2D(pos.getX(), pos.getY()-height/2),Vector2D(20,0), witdh, height, textures[4]));
		flechas--;
		scoreboard->Arrows();

	}
}

void Game::generateBalloons()
{

	if (SDL_GetTicks() >= frameBalloonTime+BALLOON_RATE)
	{
		int color = rand() % 7;
		double vel = rand() % 2 + 1;
		int posX = rand() % 300 + 400;
		balloons.push_back( new Balloon(Point2D(posX, WIN_HEIGHT), Vector2D(0, vel), 50, 50, color, textures[2], this));
		frameBalloonTime = SDL_GetTicks();
	}
	
}
void Game::AddPoints()
{
	points += POINT_ADD;
	scoreboard->Puntuacion(points);
}