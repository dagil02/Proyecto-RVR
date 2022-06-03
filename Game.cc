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
	
	// flecha1 = new Button(155, 10, 68, 68, texturas_[1], player, NULL);
	// flecha2 = new Button(225, 10, 68, 68, texturas_[1], player, NULL);
	// flecha3 = new Button(295, 10, 68, 68, texturas_[1], player, NULL);
	// flecha4 = new Button(365, 10, 68, 68, texturas_[1], player, NULL);
	// flecha5 = new Button(435, 10, 68, 68, texturas_[1], player, NULL);
	// flecha6 = new Button(505, 10, 68, 68, texturas_[1], player, NULL);
	// flecha7 = new Button(575, 10, 68, 68, texturas_[1], player, NULL);

	flecha_Texture = new Texture(renderer_, (dir + "flecha.png"), 1, 1);

	fichaRoja_Texture = new Texture(renderer_, (dir + "ficha_roja.png"), 1, 1);
	fichaAmarilla_Texture = new Texture(renderer_, (dir + "ficha_amarilla.png"), 1, 1);
	
	//inicialización del tablero
	for (int i = 0; i < TABLERO_NUM_COLUMNAS; i++){
		for (int j = 0; j < TABLERO_NUM_FILAS; j++){
			partida [i][j] = 0;
			fichasxcolumna [i] = 0;
		}
	}
	
	player->login();
}

void Game::render() {
	// Limpiamos el canvas
	SDL_RenderClear(renderer_);
	
	// flecha1->render();
	// flecha2->render();
	// flecha3->render();
	// flecha4->render();
	// flecha5->render();
	// flecha6->render();
	// flecha7->render();

	SDL_Rect flechaRect = {155, 10, 65, 65};
	flechaRect.x += flechaIndex * 69;
	flecha_Texture->render(flechaRect);

	// Renderizamos fichas ---------------------------
	SDL_Rect posIzquierdaAbajo = {160, 500, 65, 65};

	for (int x = 0; x < TABLERO_NUM_COLUMNAS; x++)
	{
		for (int y = 0; y < TABLERO_NUM_FILAS; y++)
		{
			if (partida[x][y] == 1){
				SDL_Rect r = posIzquierdaAbajo;
				r.x += x * 69;
				r.y -= y * 78;
				fichaRoja_Texture->render(r);
			} else if (partida[x][y] == 2){
				SDL_Rect r = posIzquierdaAbajo;
				r.x += x * 69;
				r.y -= y * 78;
				fichaAmarilla_Texture->render(r);
			}
		}
	}
	
	// Renderizamos tablero --------------------------
	tablero.render();

	SDL_RenderPresent(renderer_);
}

bool Game::checkWin(int jugador, int x, int y){

	int aux = 0;
	int i = 0;
	//Comprobamos horizontal
	while (i < TABLERO_NUM_COLUMNAS){
		if (partida[i][y] == jugador)
			aux++;
		else aux = 0;
		
		if (aux == 4)
			return true; 
		i++;
	}
	
	//Comprobamos vertical
	aux = 0;
	i = y;
	
	while (i >= 0){
		if (partida[x][i] == jugador)
			aux++;
		else aux = 0;
		
		if (aux == 4)
			return true; 
		i--;
	}
	
	//Diagonal \
    	//Obtener Coordenadas donde inicia la diagonal en base a fila - columna
    	int nuevaFila = x;
    	int nuevaColumna = y;
    	bool encontrado = false;
    	int total = 0;
 
 
    	while((nuevaFila != 0 || nuevaColumna != 0))
    	{
        	nuevaFila--;
        	nuevaColumna--;
 
        	if(nuevaFila == 0 || nuevaColumna == 0)
        		break;
    	}
 
    	do
    	{
        	if(nuevaFila >= TABLERO_NUM_COLUMNAS)
        		break;
 
        	if(encontrado)
        	{
            		if(partida[nuevaFila][nuevaColumna] == jugador)
            		{
                		total++;
            		}
            	else
            	{
                	encontrado = false;
                	total = 0;
            	}
        }
        if(partida[nuevaFila][nuevaColumna] == jugador && !encontrado)
        {
            encontrado = true;
            total++;
        }
 
        if(total == 4)
        {
            return true;
        }
 
        nuevaFila++;
        nuevaColumna++;
 
    }while(nuevaFila < TABLERO_NUM_COLUMNAS);
 
 
 
    //Diagonal /
    nuevaFila = x;
    nuevaColumna = y;
    encontrado = false;
    total = 0;
 
    while((nuevaFila != 0 || nuevaColumna != TABLERO_NUM_FILAS))
    {
        nuevaFila--;
        nuevaColumna++;
 
        if(nuevaFila == 0 || nuevaColumna == TABLERO_NUM_FILAS)
        break;
    }
 
    do
    {
        if(nuevaFila >= TABLERO_NUM_COLUMNAS)
        break;

        if(encontrado)
        {
            if(partida[nuevaFila][nuevaColumna] == jugador)
            {
                total++;
            }
            else
            {
                encontrado = false;
                total = 0;
            }
        }
        if(partida[nuevaFila][nuevaColumna] == jugador && !encontrado)
        {
            encontrado = true;
            total++;
        }
 
        if(total == 4)
        {
            return true;
        }
 
        nuevaFila++;
        nuevaColumna--;
 
    }while(nuevaFila < TABLERO_NUM_COLUMNAS);

	return false;
}

void Game::colocaFicha(int jugador, int columna){
	
	if (fichasxcolumna[columna] < TABLERO_NUM_FILAS){
		partida [columna][fichasxcolumna[columna]] = jugador;
		fichasxcolumna[columna]++;
		
		//Probando que comprueba bien la victoria
		bool victoria = checkWin(jugador,columna,fichasxcolumna[columna]-1);
		player->win = victoria; 
		if (victoria) std::cout << "victoria" << std::endl;
	}
}

void Game::handleEvents() {
	SDL_Event event;

	while( SDL_PollEvent( &event ) ){

		if (event.type == SDL_WINDOWEVENT){
			switch (event.window.event) {
				case SDL_WINDOWEVENT_CLOSE:   // Cerrar ventana
					exit = true;
					break;

				default:
					break;
			}
		}

		if (event.type == SDL_KEYDOWN)
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_LEFT: 
                    flechaIndex--;
                    break;
                case SDLK_RIGHT: 
                    flechaIndex++;
                    break;
                case SDLK_RETURN: 
                    if (player->turno){
                       colocaFicha(1,flechaIndex);
                       player->input(flechaIndex);
                    }
                    break;
                /*case SDLK_a: 
                    colocaFicha(2,flechaIndex);
                    break;*/
                default:
                    break; 
            }
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
	if (flechaIndex < 0) 
		flechaIndex += TABLERO_NUM_COLUMNAS;

	flechaIndex = flechaIndex % TABLERO_NUM_COLUMNAS;
}

Game::~Game() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

