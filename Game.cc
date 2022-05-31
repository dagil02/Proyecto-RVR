#include "Game.h"

Game::Game(ClientPlayer* cp) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("4 en raya", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";
std::cout << "antes del login" << std::endl;
	player = cp;
	player->login();



}

void Game::render() {
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
}

void Game::handleEvents() {
	SDL_Event evt;
}


void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (true) {
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			handleEvents();
			update();
			render();
			startTime = SDL_GetTicks();
		}
	}
	
	render();
	SDL_Delay(5000);
}

void Game::update() {
}

Game::~Game() {

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

