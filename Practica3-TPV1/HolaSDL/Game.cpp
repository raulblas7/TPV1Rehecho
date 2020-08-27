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
	arco = new Bow(Point2D(0, WIN_HEIGHT / 2), Vector2D(0, 10), 100, 100, textures[0], textures[2], this);
    objects.push_back(arco);
	events.push_back(arco);
	scoreboard = new Scoreboard(Point2D(300, 0), 25, 35, textures[5], textures[4], flechas);
	objects.push_back(scoreboard);

	generateButterfly(10);
	//game starts
	run();
}

Game::~Game()
{
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	delete arco;
	arco = nullptr;

	delete scoreboard;
	scoreboard = nullptr;

	list <GameObject*>::iterator it;
	it = objects.begin();
	while (it != objects.end()) {
		delete (*it);
		(*it) = nullptr;
		++it;
	}
//	objects.clear();
	events.clear();
	
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


	for (auto it = objects.begin(); it != objects.end(); ++it) {
		(*it)->update();
	}
	for (auto& x : objectsToDelete) {
		objects.remove(x);
		arrows.remove(dynamic_cast<Arrow*>(x));
	}
	objectsToDelete.clear();
}

void Game::render()  {
	SDL_RenderClear(renderer);
	textures[0]->render(SDL_Rect{ 0 ,0, WIN_WIDTH, WIN_HEIGHT }, SDL_FLIP_NONE);
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
}
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		for (auto it = events.begin(); it != events.end(); ++it) {
			(*it)->handleEvent(event);
		}
	}
}

bool Game::OnCollision(list<GameObject*>::iterator et)
{
	bool tocado = false;
	for (auto it = arrows.begin(); it != arrows.end(); ++it) {

		if (SDL_HasIntersection(&dynamic_cast<ArrowsGameObject*>(*et)->getDestRect(), &(*it)->getCollisionRect()))
		{
			if (dynamic_cast<Balloon*>(*et)!=nullptr)
			{
				AddPoints();
				//int prob = rand() % 2 + 1;
				//if (prob == 1) {
					auto bal = dynamic_cast<Balloon*>(*et);
					Vector2D pos = Vector2D(bal->getRect().x, bal->getRect().y+bal->getRect().h);
					CreateReward(pos, 0);
				//}
			}
			else
			{
				LessPoints();
			}
			return true;
		}
		return false;
	}
	
}

void Game::ThrowArrow(Point2D pos)
{
	if (flechas>0)
	{
		double witdh = 90;
		double height = 20;
		auto flecha= new Arrow(Point2D(pos.getX(), pos.getY() - height / 2), Vector2D(20, 0), witdh, height, textures[3], this);
		objects.push_back(flecha);
		flecha->setItList(--objects.end());
		arrows.push_back(flecha);
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
		auto globo= new Balloon(Point2D(posX, WIN_HEIGHT), Vector2D(0, -vel), 50, 50, color, textures[1], this);
		objects.push_back(globo);
		globo->setItList(--objects.end());
		frameBalloonTime = SDL_GetTicks();
	}
	
}
void Game::generateButterfly(int num)
{
	for (int i = 0; i < num; i++) {
		int posX = rand() % WIN_WIDTH + 0;
		int posY = rand() % WIN_HEIGHT + 0;
		double velX = rand() % 6 + (-3);
		double velY = rand() % 6 + (-3);
		auto butterfly = new Butterfly(Point2D(posX, posY), Vector2D(velX, velY), 50, 50, textures[6], this);
		objects.push_back(butterfly);
		butterfly->setItList(--objects.end());
	}
}
void Game::AddPoints()
{
	points += POINT_ADD;
	scoreboard->Puntuacion(points);
}

void Game::LessPoints()
{
	points -= POINT_LESS;
	scoreboard->Puntuacion(points);
}

void Game::CreateReward(Vector2D pos, int num)
{
	
	auto reward = new Reward(Point2D(pos.getX(), pos.getY()), Vector2D(0, 0.1), 50, 35, 0, textures[7], textures[8], this);
	objects.push_back(reward);
	reward->setItList(--objects.end());
	events.push_back(reward);
}

void Game::killObject(list<GameObject*>::iterator it)
{
	objectsToDelete.push_back(*it);
}
