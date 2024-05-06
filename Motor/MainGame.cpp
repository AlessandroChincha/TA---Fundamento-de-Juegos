#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor WD2M", width, height, 0);

	initShaders();

}
MainGame::~MainGame()
{


}
void MainGame::run()
{
	init();
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.02;
	/*
	for(const rect: Rectangles){
		rect[i].draw()
	}
	for(size_ti=0; i<Rectangles.size();i++){
		if(!Rentangles.empty(){
			Rectangles.draw()
		}

	}
		for (auto& sprite : sprites) {
	sprite.draw();
}
	for (const auto& rect : rectangles) {
	rect.draw();
}
	*/
	//Imprimir los triangulos dentro del arreglo de Sprites
	for (size_t i = 0; i < 20; i++) {
		if (PrintPictures[i]) {
			sprite[i].draw();
		}
	}
	//	std::cout << "Se ha generado un nuevo rectangulo" << endl;

	program.unuse();
	window->swapWindow();



}
float randomCoordGenerator() {
	std::cout << "Nueva imagen generada" << endl;
	return -static_cast<float>(rand()) / RAND_MAX;
	//return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0 - 1.0;

	//Hacer posible que salga en posiciones positivas de la pantalla

}
void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		Uint32 currentTime = SDL_GetTicks();
		
		for (size_t i = 0; i < 20; i++) {
			if (!PrintPictures[i] && currentTime - initTime > 2000 * (i + 1)) {
				sprite[i].init(randomCoordGenerator(), randomCoordGenerator(), 0.3, 0.3, "images/cat.png");
				PrintPictures[i] = true;
			}

		}
		draw();

	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x 
			<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}
