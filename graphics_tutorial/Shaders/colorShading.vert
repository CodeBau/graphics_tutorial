#version 130

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	//the z position is zero since we are ind 2D
	gl_Position.z = 0.0;
	//Indicate that coordinates are normalized 
	gl_Position.w = 1.0;
	
	fragmentColor = vertexColor;
}