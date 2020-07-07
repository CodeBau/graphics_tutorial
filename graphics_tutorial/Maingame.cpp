#include "Maingame.h"						//zalaczamy plik naglowkowy
#include "Errors.h"						    //zalaczamy plik naglowkowy					//zalaczamy plik naglowkowy

#include <iostream>						
#include <string>	



//ten plik .cpp zawiera ciala klass/funckji itd.
Maingame::Maingame() :
	_scrWidth(1024),
	_scrHight(768),
	_time(0),
	_window(nullptr), 
	_gameState (GameState::PLAY),
	_maxFPS (144.0f)
{

}

Maingame::~Maingame()
{

}

void Maingame::run()
{
	initSystem();

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	gameLoop();
}

void Maingame::initSystem()
{	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);					//zamiast jednego okna z rysunkiem, bedziemy miec 2 po jednym bedziemy rysowac a drugi bedzie sie czyscil
	

//inicjujemy SDL 
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _scrWidth, _scrHight, SDL_WINDOW_OPENGL);				//wskaznik bedzie wskazywal okno od teraz

	if (_window == nullptr)
	{
		fatalError("SDL Window culd not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context culd not be created!");
	}

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew!");
	}

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);								//RED, BLUE, GREAN, ALPHA/0,0,0, 1.0 - czarny/1,1,1, 1.0 - bialy/ to jest kolor do jakiego czysci glClear(GL_COLOR_BUFFER_BIT 

	initShaders();

}


void Maingame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribiute("vertexPosition");
	_colorProgram.addAttribiute("vertexColor");
	_colorProgram.addAttribiute("vertexUV");
	_colorProgram.linkShaders();
}
void Maingame::gameLoop()
{
	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT)		//gra ma dzialac dopoki enum class nie da EXIT
	{
		//Used for frame time masuring
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01;
		drawGame();
		calculateFPS();

		//print only once every 10 frames 
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;

		}

		float frameTicks = SDL_GetTicks() - startTicks;

		//Limit the FPS to the Max FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}


	}
}
void Maingame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))				//poniewaz to jest wskaznikiem
	{
		switch (evnt.type) 
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		//case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;

		}

	}
}

//Draws the game using the almighty OpenGL
void Maingame::drawGame()
{
	glClearDepth(1.0);												//czysci glebie 1.0 dowolna wartosc do jakiej gleboskosci ma siegnac
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				//czysci inne kolory z ekranu niz podstawowy/ zastosowano OR pojedynczy | bo to jest dzialanie na bitach

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Draw ouer sprite!
	for (int i = 0; i < _sprites.size(); i++)
		_sprites[i]->draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	//Swap ouer buffer and drwa everything to the screen!
	SDL_GL_SwapWindow(_window);
}

void Maingame::calculateFPS()
{
	static const int NUM_SAMPLE = 10;
	static float frameTimes[NUM_SAMPLE];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTickes; 
	currentTickes = SDL_GetTicks();

	_frameTime = currentTickes - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLE] = _frameTime;

	prevTicks = currentTickes;

	int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLE)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLE;
	}
	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
	
}

