#version 130
//The vertex shader operates on ech vertex 

//input data from the VBO. Ech vertex is 2 floats in vec2 vertexPosition;
in vec2 vertexPosition;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	//the z position is zero since we are ind 2D
	gl_Position.z = 0.0;
	//Indicate that coordinates are normalized 
	gl_Position.w = 1.0;
}