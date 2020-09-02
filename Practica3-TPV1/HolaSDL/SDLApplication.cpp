#include "SDLApplication.h"
#include "GameStateMachine.h"

SDLApplication::SDLApplication()
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
	gamestamac = new GameStateMachine(this);
	menu = new MainMenuState(this);
	gamestamac->pushState(menu);
	

	//game starts
	run();
}

SDLApplication::~SDLApplication()
{
	
	for (uint x = 0; x < NUM_TEXTURES; x++) delete textures[x];
	delete  menu;
	menu = nullptr;
	delete gamestamac;
	gamestamac = nullptr;
	delete play;
	play = nullptr;
	delete pause;
	pause = nullptr;
	delete end;
	end = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLApplication::run() {
	uint frameTime = SDL_GetTicks();
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
void SDLApplication::update() {
	
	gamestamac->currentState()->update();
}

void SDLApplication::render()  {
	SDL_RenderClear(renderer);
	gamestamac->currentState()->render();
		SDL_RenderPresent(renderer);
}
void SDLApplication::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		else
		{
			gamestamac->currentState()->handleEvent(event);
		}
		
	}
}

void SDLApplication::Play() {
	if (play == nullptr)
	{
		play=new PlayState(this, false);
	}
	gamestamac->pushState(play);
}

void SDLApplication::Pause() {
	if (pause == nullptr)
	{
		pause = new PauseState(this);
	}
	gamestamac->pushState(pause);
}
void SDLApplication::Exit() {
	exit = true;
}
void SDLApplication::Load() {
	if (play == nullptr) {
		play = new PlayState(this, true);
	}
	gamestamac->pushState(play);
}

void SDLApplication::Save() {
	ofstream output;
	gamestamac->popState();
	play->saveToFile(output);
	/*delete play;
	play = nullptr;
	delete menu;
	menu = nullptr;*/
	if (pause == nullptr) {
		pause = new PauseState(this);
	}
	gamestamac->pushState(pause);
	cout << "Partida guardada";
	//SDL_Quit();
}

void SDLApplication::MainMenu() {
	delete play;
	play = nullptr;
	delete end;
	end = nullptr;
	gamestamac->popState();
	gamestamac->pushState(menu);
}
void SDLApplication::GameOver() {
	if(end==nullptr)end = new EndState(this);
	gamestamac->pushState(end);
	gamestamac->changeState(end);
	cout << "Has perdido";
}

void SDLApplication::YouWin() {
	if (end == nullptr)end = new EndState(this);
	gamestamac->pushState(end);
	gamestamac->changeState(end);
	cout << "Has ganado";
}

void SDLApplication::ContinuePlaying() {
	gamestamac->popState();
	 play = dynamic_cast<PlayState*>(gamestamac->currentState());
	gamestamac->pushState(play);
}


//void SDLApplication::playState() {
//	if (play == nullptr) {
//		play = new PlayState(this);
//		play->initObjects();
//	}
//	gm->popState();
//	gm->pushState(play);
//}
//void SDLApplication::pauseState() {
//	if (pause == nullptr) pause = new PauseState(this);
//	gm->popState();
//	gm->pushState(pause);
//}
//void SDLApplication::endState(bool b) {
//	if (end == nullptr) end = new EndState(this, b);
//	gm->popState();
//	gm->pushState(end);
//}
//void SDLApplication::menuState() {
//	delete play;
//	play = nullptr;
//	delete end;
//	end = nullptr;
//	gm->popState();
//	gm->pushState(menu);
//}
//void SDLApplication::loadGame() {
//	play = new PlayState(this);
//	try {
//		play->loadGame();
//	}
//	catch (exception e) {
//		cout << e.what() << endl;
//		cout << "Se procede a crear una partida nueva" << endl;
//		play = nullptr;
//	}