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
const uint32_t FRAME_RATE = 30;


class Game
{
private:

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	Texture* texturas_[1];

	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};

	ClientPlayer* player;



public:
	Game(ClientPlayer* cp);
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();

	
	
};
	
	


	

