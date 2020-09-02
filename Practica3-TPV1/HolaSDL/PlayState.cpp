#include "PlayState.h"
#include "MenuButton.h"

PlayState::PlayState(SDLApplication* game, bool cargar_):GameState(game)
{
	cargar = cargar_;
	pauseButton = new MenuButton(Point2D(700, 0), 50, 50, game->GetTexture(10), this, PauseCallback);
	scoreboard = new Scoreboard(Point2D(300, 0), 25, 35, game->GetTexture(5), game->GetTexture(4), this);
	objects.push_back(scoreboard);
	objects.push_back(pauseButton);
	events.push_back(pauseButton);
	pauseButton->setItList(--objects.end());
	frameBalloonTime = SDL_GetTicks();
	ifstream input;
	if (cargar) {
		loadFroamFile(input);
	}
	else
	{
		Bow* arco = new Bow(Point2D(0, 100), Vector2D(0, 10), 80, 80, game->GetTexture(2), game->GetTexture(0), this);
		objects.push_back(arco);
		arco->setItList(--objects.end());
		events.push_back(arco);
		NewLevel();
	}
}

PlayState::~PlayState()
{

	delete fondo;
	
}

void PlayState::render()
{
	fondo->render(SDL_Rect{ 0 ,0, WIN_WIDTH, WIN_HEIGHT }, SDL_FLIP_NONE);

	GameState::render();
}

void PlayState::update()
{
	generateBalloons();
	GameState::update();
	for (auto ob : objectsToDelete) {

		objects.remove(ob);
		arrows.remove(static_cast<Arrow*>(ob));
		events.remove(dynamic_cast<EventHandler*>(ob));
		delete ob;
	}
	objectsToDelete.clear();


	if (mariposas == 0 || flechas < 0)
	{
		game->GameOver();

	}
}
void PlayState::handleEvent(SDL_Event& e)
{
	GameState::handleEvent(e);
	if (e.key.keysym.sym == SDLK_ESCAPE) {
		game->Pause();
	}

}
bool PlayState::OnCollision(list<GameObject*>::iterator et)
{
	bool tocado = false;
	for (auto it = arrows.begin(); it != arrows.end(); ++it) {

		if (SDL_HasIntersection(&dynamic_cast<ArrowsGameObject*>(*et)->getDestRect(), &(*it)->getCollisionRect()))
		{
			if (dynamic_cast<Balloon*>(*et) != nullptr)
			{
				(*it)->AddHit();
				AddPoints((*it)->getNHits());
				int prob = rand() % 2 + 1;
				if (prob == 1) {
					auto bal = dynamic_cast<Balloon*>(*et);
					Vector2D pos = Vector2D(bal->getDestRect().x, bal->getDestRect().y + bal->getDestRect().h);
					CreateReward(pos, 0);
				}
			}
			else if (dynamic_cast<Butterfly*>(*et) != nullptr)
			{
				LessPoints();
				mariposas--;
			}
			return true;
		}
		return false;
	}

}

void PlayState::ThrowArrow(Point2D pos)
{
	
		double witdh = 90;
		double height = 20;
		auto flecha = new Arrow(Point2D(pos.getX(), pos.getY() - height / 2), Vector2D(15, 0), witdh + arrowsSize, height + arrowsSize, game->GetTexture(3), this);
		objects.push_back(flecha);
		flecha->setItList(--objects.end());
		arrows.push_back(flecha);
		flechas--;
	
}

void PlayState::generateBalloons()
{

	if (SDL_GetTicks() >= frameBalloonTime + BALLOON_RATE)
	{
		int color = rand() % 7;
		double vel = rand() % (int)(Vel_Bal.max - Vel_Bal.min) + Vel_Bal.min;
		int posX = rand() % 300 + 400;
		auto globo = new Balloon(Point2D(posX, WIN_HEIGHT), Vector2D(0, -vel), 50, 50, color, game->GetTexture(1), this);
		objects.push_back(globo);
		globo->setItList(--objects.end());
		frameBalloonTime = SDL_GetTicks();
	}

}
void PlayState::generateButterfly()
{
	for (int i = 0; i < mariposas; i++) {
		int posX = rand() % (WIN_WIDTH - 50) + 0;
		int posY = rand() % (WIN_HEIGHT - 50) + 0;
		double velX = rand() % (int)(Vel_But.max - Vel_But.min) + Vel_But.min;
		double velY = rand() % (int)(Vel_But.max - Vel_But.min) + Vel_But.min;
		auto butterfly = new Butterfly(Point2D(posX, posY), Vector2D(velX, velY), 50, 50, game->GetTexture(6), this);
		objects.push_back(butterfly);
		butterfly->setItList(--objects.end());
	}
}
void PlayState::AddPoints(int numhits)
{
	points += POINT_ADD + pow(numhits - 1, 2) * POINT_ADD;
	if (points / 100 > level) {
		NewLevel();
	}
	scoreboard->Puntuacion(points);
}

void PlayState::LessPoints()
{
	points -= POINT_LESS;
	scoreboard->Puntuacion(points);
}

void PlayState::CreateReward(Vector2D pos, int num)
{
	int color = rand() % 2;
	Reward* premio = nullptr;
	switch (color)
	{
	case 0: premio = new GiveMeArrows(pos, Vector2D(0, 0.1), 50, 35, game->GetTexture(7),  game->GetTexture(8),color,this);
		break;
	case 1: premio = new BigArrows(pos, Vector2D(0, 0.1), 50, 35,  game->GetTexture(7),  game->GetTexture(8), color, 3000,this);
		break;
	}
	events.push_back(premio);
	auto et = objects.insert(objects.end(), premio);
	premio->setItList(et);
}

void PlayState::killObject(list<GameObject*>::iterator it)
{
	objectsToDelete.push_back(*it);
}

void PlayState::NewLevel()
{
	level++;
	if (level < NUM_Lvl) {
		for (auto& x : objects) {
			if (dynamic_cast<Scoreboard*>(x) == nullptr && dynamic_cast<Bow*>(x) == nullptr  && dynamic_cast<MenuButton*>(x) == nullptr)
			{
				objectsToDelete.push_back(x);
			}

		}
		if (fondo != nullptr)
		{
			delete fondo;
			fondo = nullptr;
			
		}
		fondo = new Texture(game->GetRenderer(), niveles[level].filename, 1, 1);
		flechas = niveles[level].numFlecha;
		mariposas = niveles[level].numMariposas;
		Vel_Bal = niveles[level].velBal;
		Vel_But = niveles[level].velBut;
		generateButterfly();
	}
	else { game->YouWin(); }

}

void PlayState::saveToFile(ofstream& output) {
	//abrimos el archivo
	output.open("guardados.txt");
	//si no se abre lanzamos excepcion
	if (!output.is_open()) throw FileNotFoundError("No se encuentra el archivo");
	//si se puede abrir guardamos la partida
	else {
		output << level << endl;
		output << points << endl;
		output << flechas << endl;
		output << mariposas << endl;
		int objetos = objects.size();
		output << objetos << endl;
		for (auto it = ++objects.begin(); it != objects.end(); ++it) {
			auto ob = dynamic_cast<ArrowsGameObject*>(*it);
			if (ob!=nullptr)
			{
				ob->saveToFile(output);

			}
		}
	}
	output.close();

}

void PlayState::loadFroamFile(ifstream& input) {

	//abrimos el archivo
	input.open("guardados.txt");
	//si no se puede abrir lanzamos una excepcion
	if (!input.is_open()) throw FileNotFoundError("No se encuentra el archivo");
	//si se abre cargamos el archivo
	else {
		input >> level;
		fondo = new Texture(game->GetRenderer(), niveles[level].filename, 1, 1);
		Vel_Bal = niveles[level].velBal;
		Vel_But = niveles[level].velBut;
		input >> points;
		scoreboard->Puntuacion(points);
		input >> flechas;
		input >> mariposas;
		int obj;
		int color;
		input >> obj;
		string line;
		for (int i = 0; i < obj; i++) {
			input >> line;
			//falta que cada objeto sepa cual es su textura
			if (line == "Mariposa")objects.push_back(new Butterfly(Point2D(NULL, NULL), Vector2D(NULL, NULL), 20, 20,  game->GetTexture(6), this));
			else if (line == "Globo")objects.push_back(new Balloon(Point2D(NULL, NULL), Vector2D(NULL, NULL), 20, 20, 0,  game->GetTexture(1), this));
			else if (line == "Flecha")
			{
				objects.push_back(new Arrow(Point2D(NULL, NULL), Vector2D(NULL, NULL), 20, 20,  game->GetTexture(3), this));
				arrows.push_back(dynamic_cast<Arrow*>(objects.back()));
			}
			else if (line == "Arco") {
				objects.push_back(new Bow(Point2D(0, 0), Vector2D(0, 0), 20, 20, game->GetTexture(2), game->GetTexture(0), this));
				events.push_back(dynamic_cast<EventHandler*>(objects.back()));
			}
			else if (line == "Premio") {

				input >> color;
				switch (color)
				{
				case 0:
					objects.push_back(new GiveMeArrows(Point2D(0, 0), Vector2D(0, 0), 20, 20,  game->GetTexture(7),  game->GetTexture(8), color,this));
					break;
				case 1:
					objects.push_back(new BigArrows(Point2D(0, 0), Vector2D(0, 0), 20, 20,  game->GetTexture(7),  game->GetTexture(8),  color, 3000,this));
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

void PlayState::ArrowSize(double prop)
{
	arrowsSize += prop;
}

void PlayState::AddArrows(int num)
{
	flechas += num;
}

