#include "Maingame.h"						//zalaczamy plik naglowkowy
#include "Errors.h"						    //zalaczamy plik naglowkowy					//zalaczamy plik naglowkowy
#include "ImageLoader.h"

#include <iostream>						
#include <string>	



//ten plik .cpp zawiera ciala klass/funckji itd.
Maingame::Maingame() :
	_scrWidth(1024),
	_scrHight(768),
	_time(0),
	_window(nullptr), 
	_gameState (GameState::PLAY)					
{

}

Maingame::~Maingame()
{

}

void Maingame::run()
{
	initSystem();
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	_playerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

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
	while (_gameState != GameState::EXIT)		//gra ma dzialac dopoki enum class nie da EXIT
	{
		processInput();
		_time += 0.01;
		drawGame();
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

		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;

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
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Draw ouer sprite!
	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	//Swap ouer buffer and drwa everything to the screen!
	SDL_GL_SwapWindow(_window);
}
