#include <iostream>						
#include <string>						

#include "Maingame.h"						//zalaczamy plik naglowkowy

//warunek sprawdzajacy czy nasze okno sie nie wykrzaczylo
void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout<<"Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();						         //najprostsza komenda konczaca SDL
}

//ten plik .cpp zawiera ciala klass/funckji itd.
Maingame::Maingame()						//definicja konstruktora dla Maingame
{
	_window = nullptr;						//zabespieczenie przed bugiem pomiedzy inicjacja okna a jego wywolaniem (obiekt bez atrybutow)
											//ze wzgledu na to ze SDL_Window* jest wskaznikiem _window musi wskazywac nic. 
	_scrWidth = 1024;
	_scrHight = 768;
	_gameState = GameState::PLAY;
}

Maingame::~Maingame()
{

}

void Maingame::run()
{
	initSystem();
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

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew!");
	}

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);								//RED, BLUE, GREAN, ALPHA/0,0,0, 1.0 - czarny/1,1,1, 1.0 - bialy/ to jest kolor do jakiego czysci glClear(GL_COLOR_BUFFER_BIT 

}
void Maingame::gameLoop()
{
	while (_gameState != GameState::EXIT)		//gra ma dzialac dopuki enum class nie da EXIT
	{
		processInput();
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

void Maingame::drawGame()
{
	glClearDepth(1.0);												//czysci glebie 1.0 dowolna wartosc do jakiej gleboskosci ma siegnac
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				//czysci inne kolory z ekranu niz podstawowy/ zastosowano OR pojedynczy | bo to jest dzialanie na bitach


	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 0.5f);						//w pikselach
	glVertex2f(0.5f, 0.5f);


	glEnd();

	SDL_GL_SwapWindow(_window);
}
