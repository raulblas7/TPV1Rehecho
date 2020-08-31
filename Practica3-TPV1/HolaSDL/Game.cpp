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
	NewLevel();
	// We finally create the game objects
	arco = new Bow(Point2D(0, WIN_HEIGHT / 2), Vector2D(0, 10), 100, 100, textures[2], textures[0], this);
    objects.push_back(arco);
	events.push_back(arco);
	scoreboard = new Scoreboard(Point2D(300, 0), 25, 35, textures[5], textures[4], this);
	objects.push_back(scoreboard);

	//game starts
	run();
}

Game::~Game()
{

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
	objects.clear();
	events.clear();
	
	for (uint x = 0; x < NUM_TEXTURES; x++) delete textures[x];
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
	if (mariposas > 0) {
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
	else { cout << "HAS PERDIDO BRO" << endl; exit = true; }
}

void Game::render()  {
	SDL_RenderClear(renderer);
	fondo->render(SDL_Rect{ 0 ,0, WIN_WIDTH, WIN_HEIGHT }, SDL_FLIP_NONE);
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
				(*it)->AddHit();
				AddPoints((*it)->getNHits());
				int prob = rand() % 2 + 1;
				if (prob == 1) {
					auto bal = dynamic_cast<Balloon*>(*et);
					Vector2D pos = Vector2D(bal->getDestRect().x, bal->getDestRect().y+bal->getDestRect().h);
					CreateReward(pos, 0);
				}
			}
			else if(dynamic_cast<Butterfly*>(*et) != nullptr)
			{
				LessPoints();
				mariposas--;
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
		auto flecha= new Arrow(Point2D(pos.getX(), pos.getY() - height / 2), Vector2D(15, 0), witdh + arrowsSize, height + arrowsSize, textures[3], this);
		objects.push_back(flecha);
		flecha->setItList(--objects.end());
		arrows.push_back(flecha);
		flechas--;
	}
}

void Game::generateBalloons()
{

	if (SDL_GetTicks() >= frameBalloonTime+BALLOON_RATE)
	{
		int color = rand() % 7;
		double vel = rand() % (int)(Vel_Bal.max - Vel_Bal.min) + Vel_Bal.min;
		int posX = rand() % 300 + 400;
		auto globo= new Balloon(Point2D(posX, WIN_HEIGHT), Vector2D(0, -vel), 50, 50, color, textures[1], this);
		objects.push_back(globo);
		globo->setItList(--objects.end());
		frameBalloonTime = SDL_GetTicks();
	}
	
}
void Game::generateButterfly()
{
	for (int i = 0; i < mariposas; i++) {
		int posX = rand() % (WIN_WIDTH-50) + 0;
		int posY = rand() % (WIN_HEIGHT-50) + 0;
		double velX = rand() % (int)(Vel_But.max-Vel_But.min) + Vel_But.min;
		double velY = rand() % (int)(Vel_But.max - Vel_But.min) + Vel_But.min;
		auto butterfly = new Butterfly(Point2D(posX, posY), Vector2D(velX, velY), 50, 50, textures[6], this);
		objects.push_back(butterfly);
		butterfly->setItList(--objects.end());
	}
}
void Game::AddPoints(int numhits)
{
	points += POINT_ADD+ pow(numhits - 1, 2) * POINT_ADD;
	if (points / 100 >  level) {
		NewLevel();
	}
	scoreboard->Puntuacion(points);
}

void Game::LessPoints()
{
	points -= POINT_LESS;
	scoreboard->Puntuacion(points);
}

void Game::CreateReward(Vector2D pos, int num)
{
	int color = rand() % 2;
	Reward* premio = nullptr;
	switch (color)
	{
	case 0: premio = new GiveMeArrows(pos, Vector2D(0, 0.1), 50, 35, textures[7], textures[8], this, color);
		break;
	case 1: premio = new BigArrows(pos, Vector2D(0, 0.1), 50, 35, textures[7], textures[8], this, color,3000);
		break;
	}
	events.push_back(premio);
	auto et = objects.insert(objects.end(), premio);
	premio->setItList(et);
}

void Game::killObject(list<GameObject*>::iterator it)
{
	objectsToDelete.push_back(*it);
}

void Game::NewLevel()
{
	level++;
	if (level < NUM_Lvl) {
		for (auto& x : objects) {
			if (dynamic_cast<Scoreboard*>(x) == nullptr && dynamic_cast<Bow*>(x) == nullptr)
			{
				objectsToDelete.push_back(x);
			}

		}
		fondo = new Texture(renderer, niveles[level].filename, 1, 1);
		flechas = niveles[level].numFlecha;
		mariposas = niveles[level].numMariposas;
		Vel_Bal = niveles[level].velBal;
		Vel_But = niveles[level].velBut;
		generateButterfly();
	}
	else { cout << "HAS GANADO!" << endl; exit = true; }

}

void Game::saveToFile(ofstream& output) {
	//abrimos el archivo
	output.open("guardados.txt");
	//si no se abre lanzamos excepcion
	if (!output.is_open()) throw FileNotFoundError("No se encuentra el archivo");
	//si se puede abrir guardamos la partida
	else {
		output << level << endl;
		output << points << endl;
		output << flechas << endl;
		int objetos = objects.size();
		output << objetos << endl;
		for (auto it = ++objects.begin(); it != objects.end(); ++it) {
			dynamic_cast<ArrowsGameObject*>(*it)->saveToFile(output);
		}
	}
	output.close();

}

void Game::loadFroamFile(ifstream& input) {

	//abrimos el archivo
	input.open("guardados.txt");
	//si no se puede abrir lanzamos una excepcion
	if (!input.is_open()) throw FileNotFoundError("No se encuentra el archivo");
	//si se abre cargamos el archivo
	else {
		input >> level;
		fondo = new Texture(renderer, niveles[level].filename, 1, 1);
		Vel_Bal = niveles[level].velBal;
		Vel_But = niveles[level].velBut;
		input >> points;
		scoreboard->Puntuacion(points);
		input >> flechas;
		
		int obj;
		int color;
		input >> obj;
		string line;
		for (int i = 0; i < obj; i++) {
			input >> line;
			//falta que cada objeto sepa cual es su textura
			if (line == "Mariposa")objects.push_back(new Butterfly(Point2D(NULL, NULL), Vector2D(NULL, NULL), 20, 20, textures[6], this));
			else if (line == "Globo")objects.push_back(new Balloon(Point2D(NULL, NULL), Vector2D(NULL, NULL), 20, 20, 0, textures[1], this));
			else if (line == "Flecha")
			{
				objects.push_back(new Arrow(Point2D(NULL, NULL), Vector2D(NULL, NULL),20,20, textures[3], this));
				arrows.push_back(dynamic_cast<Arrow*>(objects.back()));
			}
			else if (line == "Arco") {
				objects.push_back(new Bow(Point2D(0, 0), Vector2D(0, 0), 20, 20, textures[0], textures[2], this));
				events.push_back(dynamic_cast<EventHandler*>(objects.back()));
			}
			else if (line == "Premio") {

				input >> color;
				switch (color)
				{
				case 0:
					objects.push_back(new GiveMeArrows(Point2D(0, 0), Vector2D(0, 0), 20, 20, textures[7], textures[8], this, color));
					break;
				case 1:
					objects.push_back(new BigArrows(Point2D(0, 0), Vector2D(0, 0), 20, 20, textures[7], textures[8], this, color,3000));
					break;

				}
				events.push_back(dynamic_cast<EventHandler*>(objects.back()));
			}
			else
			{
				throw FileFormatError("Formato de archivo incorrecto");
			}
			dynamic_cast<ArrowsGameObject*>(objects.back())->loadFromFile(input);
			dynamic_cast<ArrowsGameObject*>(objects.back())->setItList(--objects.end());
		}
	}
	input.close();
}

void Game::ArrowSize(double prop)
{
	arrowsSize += prop;
}

void Game::AddArrows(int num)
{
	flechas+=num;
}
