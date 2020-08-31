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
	delete gamestamac;
	delete play;
	delete pause;
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
	gamestamac->changeState(new PlayState(this, true));
}

void SDLApplication::Save() {
	ofstream output;
	gamestamac->popState();
	dynamic_cast<PlayState*>(gamestamac->currentState())->saveToFile(output);
	gamestamac->pushState(new PauseState(this));
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
	EndState* end = new EndState(this);
	gamestamac->pushState(end);
	gamestamac->changeState(end);
	cout << "Has perdido";
}

void SDLApplication::YouWin() {
	EndState* end = new EndState(this);
	gamestamac->pushState(end);
	gamestamac->changeState(end);
	cout << "Has ganado";
}

void SDLApplication::ContinuePlaying() {
	gamestamac->popState();
	 play = dynamic_cast<PlayState*>(gamestamac->currentState());
	gamestamac->pushState(play);
}


