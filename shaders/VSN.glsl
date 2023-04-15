#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_map;

out vec3 vpos;
out vec3 fpos;
out vec2 vmap;

out vec3 normal;

out vec3 view_pos;

uniform mat4 model, view, proj;

uniform vec3 camera_pos;

void main(){

    gl_Position = vec4(vertex_position, 1.0) * model * view * proj;

    vmap = vertex_map;
    vpos = vertex_position;
    fpos = vec3(model * vec4(vertex_position, 1.0));
    normal = vertex_normal;

    // UTILIZAR MATRIZ DE CAMARA!!!!

    view_pos = camera_pos;

}