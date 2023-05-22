#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_map;

out vec3 fpos;
out vec3 normal;
out vec2 vmap;

out vec3 view_pos;

out mat4 view_m;

uniform mat4 model, view, proj;

uniform vec3 camera_pos;

void main(){

    fpos = vec3(vec4(vertex_position, 1.0) * model * view);
    vmap = vertex_map;
    normal = vertex_normal;

    // UTILIZAR MATRIZ DE CAMARA!!!!

    view_pos = camera_pos;
    view_m = view;

    gl_Position = vec4(vertex_position, 1.0) * model * view * proj;

}