#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include <vector>
using namespace std;
enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	int width;
	int height;
	SDL_Window* window;
	Uint32 initTime;
	//vector<Sprites> Rectangles Intento fallido de hacerlo con un Vector
	Sprite sprites[20]; //Definir una cantidad exacta de cuadros limite a imprimir
	bool PrintRectangles[20]; //Definir como un arreglo para que se defina la cantidad maxima que se pueden imprimir
	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
};