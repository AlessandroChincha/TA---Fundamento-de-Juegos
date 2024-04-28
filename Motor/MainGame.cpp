#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame() : initTime(0){
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("nombre_ventana_xd", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();

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
		if (PrintRectangles[i]) {
			sprites[i].draw();
		}
	}
//	std::cout << "Se ha generado un nuevo rectangulo" << endl;

	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::run()
{
	init();
	update();
}

float randomCoordGenerator() {
	std::cout << "Nuevo rectanculo generado" << endl;
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * -1.0;
	//return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0 - 1.0;

	//Hacer posible que salga en posiciones positivas de la pantalla

}
void MainGame::update()
{
	
	//int RandomPosition = static_cast<float>(rand() / 2) / static_cast<float>(RAND_MAX) * -1.0;
	while (gameState != GameState::EXIT) {
		processInput();
		Uint32 currentTime = SDL_GetTicks();

		for (size_t i = 0; i < 20; i++) {
			if (!PrintRectangles[i] && currentTime - initTime > 2000 * (i + 1)) {
				sprites[i].init(randomCoordGenerator(), randomCoordGenerator(), 1, 1);
				PrintRectangles[i] = true;
			}
		}
		draw();
	}
	/*
	    while (gameState != GameState::EXIT) {
        processInput();
        Uint32 currentTime = SDL_GetTicks();

        for (size_t i = 0; i < 20; i++) {
            if (currentTime - initTime > 2000 * (i + 1)) {
                Sprite newSprite;
                newSprite.init(randomCoord(), randomCoord(), 0.5, 0.5);
                sprites.push_back(newSprite);
                initTime = currentTime;
            }
        }
        draw();
    }
	*/
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
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
	program.linkShader();

}

MainGame::~MainGame()
{
}