#include "Sprite.h"
#include "Vertex.h"

#include <cstdlib>



Sprite::Sprite()
{
	_vboID=0;
}

Sprite::~Sprite()
{
	if(_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	
	if (_vboID == 0){
		glGenBuffers(1, &_vboID);							//1 - bo jeden buffer
	}
	
	Vertex vertexData[6];

	//First Triangle

	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)				//6 - bo tyle dalismy w VertexData
	{
		vertexData[i].setColor(255, 0, 0, 0);

	}

	
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	//blind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Tell opengl taht we want to use the first attribiute array.
	//We only need one array right now sice we are only using position.
	glEnableVertexAttribArray(0);

	//This is the position attribiute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); 
	
	//This is the color attribiute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));  	//2 bo dwawymiary x i y 

	//This is UV attribiut pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));  	

	//Draw the 6 vertics to the screen 
	glDrawArrays(GL_TRIANGLES,0,6);

	//Disable the vertec atrib array. This is not optional.
	glDisableVertexAttribArray(0);

	//Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
