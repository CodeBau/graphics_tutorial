#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	//the z position is zero since we are ind 2D
	gl_Position.z = 0.0;
	//Indicate that coordinates are normalized 
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
	fragmentUV=vec2(vertexUV.x, 1.0-vertexUV.y);
}