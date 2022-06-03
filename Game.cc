#include "Game.h"

Game::Game(ClientPlayer* cp) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Konnekta IV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";
	
	// Assinamos el cliente del jugador
	player = cp;

	// Creamos las texturas
	flecha_Texture = new Texture(renderer_, (dir + "flecha.png"), 1, 1);
	fichaRoja_Texture = new Texture(renderer_, (dir + "ficha_roja.png"), 1, 1);
	fichaAmarilla_Texture = new Texture(renderer_, (dir + "ficha_amarilla.png"), 1, 1);
	tablero_Texture = new Texture(renderer_, (dir + "tablero.png"), 1, 1);
	victoria_Texture = new Texture(renderer_, (dir + "victoria.png"), 1, 1);
	derrota_Texture = new Texture(renderer_, (dir + "derrota.png"), 1, 1);
	
	tablero.setValue(139, 79, 520, 520, tablero_Texture);
	
	// Inicialización del tablero
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

	SDL_Rect flechaRect = {155, 10, 65, 65};
	flechaRect.x += flechaIndex * 69;

	if (player->pi->_miTurno && !finDePartida)
		flecha_Texture->render(flechaRect);

	if (finDePartida)
	{
		SDL_Rect bannerRect = {215, -20, 370, 120};
		if (ganadorId == player->pi->_id)
			victoria_Texture->render(bannerRect);
		else
			derrota_Texture->render(bannerRect);
	}

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

bool Game::hasPlayerWon(int jugador, int x, int y){

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

void Game::checkForEndOfGame(int columna){
	// Hacemos la comprobacion de victoria
	bool victoriaYo = hasPlayerWon(player->pi->_id+1,columna,fichasxcolumna[columna]-1);
	bool victoriaOtro = hasPlayerWon(player->piEnemy->_id+1,columna,fichasxcolumna[columna]-1);
	
	if (victoriaOtro)
	{
		std::cout << "---- Derrota ----" << std::endl;
		finDePartida = true;
		ganadorId = player->piEnemy->_id;
	}
	else if (victoriaYo)
	{
		std::cout << "---- Victoria ----" << std::endl;
		finDePartida = true;
		ganadorId = player->pi->_id;
	}
	
	if (finDePartida)
		render();
}

void Game::colocaFicha(int jugador, int columna, bool fichaEnemiga, int teclaId){

	if (finDePartida) return;

	if (player->pi->_id == teclaId)
	{
		if ((player->pi->_miTurno || fichaEnemiga) && fichasxcolumna[columna] < TABLERO_NUM_FILAS){
			partida [columna][fichasxcolumna[columna]] = jugador;
			fichasxcolumna[columna]++;
			
			if(!fichaEnemiga)
			{
				player->pi->_miTurno = false;
				player->pi->_columnaSeleccionada = columna;
				player->sendMessage();
				render();
			}
			
			checkForEndOfGame(columna);
		}
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
                case SDLK_r:
                    colocaFicha(player->pi->_id+1,flechaIndex, false, 0);
                    break;
				case SDLK_a:
                    colocaFicha(player->pi->_id+1,flechaIndex, false, 1);
                    break;
                default:
                    break; 
            }
        }
	}
}


void Game::run() {
	std::cout << "Game running..." << std::endl;
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			render();
			handleEvents();
			update();
			render();
			startTime = SDL_GetTicks();
		}
	}
	
	render();
	SDL_Delay(5000);
}

void clearEvents(){
	SDL_Event e;
	while (SDL_PollEvent(&e));
}

void Game::update() {
	if (finDePartida) return;

	if (flechaIndex < 0) 
		flechaIndex += TABLERO_NUM_COLUMNAS;
	flechaIndex = flechaIndex % TABLERO_NUM_COLUMNAS;

	// Comprobamos que sea nuestro turno, en caso de que no, 
	// esperamos a recibir la respuesta con la jugada del otro jugados
	if (player->update())
	{
		// Procesar la jugada recibida del otro jugador
		colocaFicha(player->piEnemy->_id+1, player->piEnemy->_columnaSeleccionada, true, player->pi->_id);

		// Indicamos que le toca a este jugador
		player->pi->_miTurno = true;

		// Limpiamos el buffer de eventos de SDL por si se ha intentado poner 
		// fichas mientras se esperaba la respuesta del otro jugador
		clearEvents();
	}
}

Game::~Game() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

