#version 460

in vec2 tc;
uniform sampler2D basic_texture;
out vec4 frag_colour;

void main() {
	vec4 texel = texture (basic_texture, tc);
	frag_colour = texel;
}