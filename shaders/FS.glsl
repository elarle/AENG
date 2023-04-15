#version 460

uniform sampler2D text1;

in vec2 tc;
in vec3 color;

out vec4 frag_colour;

void main() {
	frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
}