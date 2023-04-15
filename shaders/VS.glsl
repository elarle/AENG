#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_map;

out vec2 tc;
out vec3 color;

uniform mat4 model, view, proj;

void main() {
	tc = vertex_map;
	//gl_Position = proj * view * model * vec4(vertex_position, 1.0);
	gl_Position = vec4 (vertex_position, 1.0);
}