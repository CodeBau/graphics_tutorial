#pragma once

#include <GL/glew.h>

struct Vertex {
	struct Position {
		float x;
		float y;
	} position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	}color;
									//minimalizujemy wartosc, zeby zoptymalizowac wykorzystanie pamieci.
									// GLubytes to jest GL unsigned byte [4]- bo mamy red,green,red,alpha 
									//alpha to jest transparency 

};