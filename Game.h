#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include <string>
#include <iostream>
#include "Chat.h"
#include "Button.h"
#include "GameObject.h"

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_SPRITES = 2;
const string dir = "Sprites/";
const uint32_t FRAME_RATE = 30;

const int TABLERO_NUM_COLUMNAS = 7;
const int TABLERO_NUM_FILAS = 6;



class Game
{
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	bool finDePartida = false;
	int ganadorId = -1;
	
	ClientPlayer* player;
	
	int partida[TABLERO_NUM_COLUMNAS][TABLERO_NUM_FILAS];
	int fichasxcolumna[TABLERO_NUM_COLUMNAS];

	GameObject tablero;

	int flechaIndex = 0;

	Texture* tablero_Texture;
	Texture* flecha_Texture;
	Texture* fichaRoja_Texture;
	Texture* fichaAmarilla_Texture;
	Texture* victoria_Texture;
	Texture* derrota_Texture;

public:
	Game(ClientPlayer* cp);
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();
	void colocaFicha(int jugador, int columna, bool fichaEnemiga, int teclaId);
	bool hasPlayerWon(int jugador, int x, int y);
	void checkForEndOfGame(int columna);
};