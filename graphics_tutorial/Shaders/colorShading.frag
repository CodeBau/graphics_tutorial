#version 130
//The fragment shader oparets on ech pixel in a give polygon

//This is the 3 component float vector that gests outputted to the screen for each pixel.

out vec3 color;

void main() {
	//Just hardcode the color to red
	color = vec3(1.0, 0.0, 0.0);
}