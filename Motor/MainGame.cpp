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

	for (size_t i = 0; i < 12; i++) {
		if (spriteInitialized[i]) {
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

float randomCoord() {
	std::cout << "Nuevo rectanculo generado" << endl;
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * -1.0;

}
void MainGame::update()
{
	int RandomPosition = static_cast<float>(rand() / 2) / static_cast<float>(RAND_MAX) * -1.0;
	while (gameState != GameState::EXIT) {
		processInput();
		Uint32 currentTime = SDL_GetTicks();

		for (size_t i = 0; i < 12; i++) {
			if (!spriteInitialized[i] && currentTime - initTime > 2000 * (i + 1)) {
				sprites[i].init(randomCoord(), randomCoord(), 0.5, 0.5);
				spriteInitialized[i] = true;
			}
		}
		draw();
	}
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