#version 460

in vec3 color;
out vec4 frag_colour;
in float dist;

void main() {
	frag_colour = vec4 (1.0, 1.0, 1.0, 1.0);
	frag_colour.xyz *= dist;
}
