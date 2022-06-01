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


class Game
{
private:

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	Texture* texturas_[NUM_SPRITES];

	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};
	
	TexturesAtributes atributes_[NUM_SPRITES] = { "tablero.png", 1, 1, "flecha.png",1,1};

	ClientPlayer* player;

	GameObject tablero;
	
	Button* flecha1;
	Button* flecha2;
	Button* flecha3;
	Button* flecha4;
	Button* flecha5;
	Button* flecha6;
	Button* flecha7;

public:
	Game(ClientPlayer* cp);
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();
};
	
	


	

