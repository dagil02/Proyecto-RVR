#include "Game.h"

Game::Game(ClientPlayer* cp) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("4 en raya", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";
		//std::cout << "antes de texturas" << std::endl;
		for (int i = 0; i < NUM_SPRITES; i++) {
			texturas_[i] = new Texture(renderer_, (dir + atributes_[i].nombre), atributes_[i].row, atributes_[i].col);
	}
	//std::cout << "despues de texturas" << std::endl;
	tablero.setValue(139, 79, 520, 520, texturas_[0]);
	
	//std::cout << "antes del login" << std::endl;
	player = cp;
	
	flecha1 = new Button(155, 10, 68, 68, texturas_[1], player, NULL);
	flecha2 = new Button(225, 10, 68, 68, texturas_[1], player, NULL);
	flecha3 = new Button(295, 10, 68, 68, texturas_[1], player, NULL);
	flecha4 = new Button(365, 10, 68, 68, texturas_[1], player, NULL);
	flecha5 = new Button(435, 10, 68, 68, texturas_[1], player, NULL);
	flecha6 = new Button(505, 10, 68, 68, texturas_[1], player, NULL);
	flecha7 = new Button(575, 10, 68, 68, texturas_[1], player, NULL);

	ficha_roja = new Texture(renderer_, (dir + "ficha_roja.png"), 1, 1);
	ficha_amarilla = new Texture(renderer_, (dir + "ficha_amarilla.png"), 1, 1);
	
	player->login();
}

void Game::render() {
	SDL_RenderClear(renderer_);
	
	flecha1->render();
	flecha2->render();
	flecha3->render();
	flecha4->render();
	flecha5->render();
	flecha6->render();
	flecha7->render();

	// Renderizamos fichas ---------------------------
	SDL_Rect posIzquierdaAbajo = {160, 500, 65, 65};

	for (int x = 0; x <= 6; x++)
	{
		for (int y = 0; y <= 5; y++)
		{
			SDL_Rect r = posIzquierdaAbajo;
			r.x += x * 69;
			r.y -= y * 78;
			ficha_roja->render(r);
		}
	}
	
	// Renderizamos tablero --------------------------
	tablero.render();

	SDL_RenderPresent(renderer_);
}

void Game::handleEvents() {
	SDL_Event event;

	while( SDL_PollEvent( &event ) ){
		switch (event.type) {
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:   // Cerrar ventana
						exit = true;
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}


void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
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

