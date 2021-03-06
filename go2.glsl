#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 fColor; // output a color to the fragment shader
out vec2 MausePos;

uniform float x = 400;
uniform float y = 300;

void main() {
	MausePos = vec2(x,y);
	gl_Position = vec4(aPos.x-((400-x)/400), aPos.y+((300-y)/300), aPos.z, 1.0);
    fColor = vec4(aColor, 1.0); // set ourColor to the input color we got from the vertex data
}
