#pragma once							//cos co zabespiecza przed zapetleniem

#include<SDL/SDL.h>
#include<GL/glew.h>

enum class GameState { PLAY, EXIT };		//silny typ wyliczeniowy (ang. strongly-typed enums). https://devcode.pl/cpp11-enum-class/

//to sa same naglowki bo to jest plik .h
class Maingame							//klasa gra g��wna
{

public:
	Maingame();							//konstruktor gra g�owna 
	~Maingame();						//destruktor gra glowna

	void run();
	

private:
	void initSystem();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;				//prywatna zmienna inicjujaca okno, oraz podstawowe czynnosci zwiazne z oknem 
	int _scrWidth;
	int	_scrHight;
	GameState _gameState;

};

