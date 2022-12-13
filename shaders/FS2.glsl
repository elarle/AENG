#version 460

in vec3 color;
out vec4 frag_colour;
in float dist;

void main() {
	frag_colour = vec4 (color, 1.0);
}