#version 460

/*
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

uniform mat4 view, proj;

out vec3 color;

void main() {
	color = vertex_color;
	gl_Position = vec4(vertex_position, 1.0);
	//gl_Position = proj * view * vec4 (vertex_position, 1.0);
}
*/
out vec3 color;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

uniform mat4 model, view, proj;
// use z position to shader darker to help perception of distance
out float dist;

void main() {
	color = vertex_color;
	gl_Position = proj * view * model * vec4(vertex_position, 1.0);
	//gl_Position = proj * view * model * vec4 (vertex_position, 1.0);
	dist = vertex_position.z;//1.0 - (-pos_eye.z / 10.0);
}