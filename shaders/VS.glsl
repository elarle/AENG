#version 460

out vec2 tc;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_texture;

uniform mat4 model, view, proj;

void main() {
	tc = vertex_texture;
	//gl_Position = proj * view * model * vec4(vertex_position, 1.0);
	gl_Position = vec4 (vertex_position, 1.0) * model * view * proj;
}