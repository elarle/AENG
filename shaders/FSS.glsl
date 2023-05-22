#version 460

out vec4 frag_color;

in vec3 fpos;
in vec2 vmap;

in vec3 normal;
in vec3 view_pos;

in mat4 view_m;

uniform sampler2D texture_s;

uniform vec3 light_pos;
uniform vec3 light_color;

void main(){

    vec3 lp_p = vec3(vec4(2.0, 3.0, 1.0, 1.0));
    //mat4 i = inverse(view_m * lp_p);
    //lp_p = vec3(vec4(lp_p, 1.0) * i);

    /* light_pos = vec3(lp_p); */

    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(lp_p - fpos);

    float diff = max(dot(norm, light_direction), 0.0);

    vec3 reflect_direction = reflect(-light_direction, norm);
    vec3 view_dir = normalize(view_pos - fpos);

    //                                                          SHINY
    float spec = pow(max(dot(view_dir, reflect_direction), 0.0), 1.0);

    float dist = length(light_pos - fpos);
    float atenuation = 1.0 / (1.0 + 0.7 * dist + 1.8 * (dist*dist));

    float ambient_f = 0.0;
    float diffuse_f = 0.4;
    float specular_f = 0.5;

    vec3 ambient = ambient_f * vec3(1.0, 1.0, 1.0);
    vec3 diffuse = diffuse_f * diff * vec3(1.0, 1.0, 1.0);
    vec3 specular = specular_f * spec * vec3(1.0, 1.0, 1.0);

    vec3 l = (ambient + diffuse + specular);

    frag_color = vec4(l * texture( texture_s, vmap ).rgb, 1.0);

  /* // AMBIENT LIGHTING (Global)

  float ambientStrength = 0.0;
  vec3 ambient = ambientStrength * vec3(0.5, 0.5, 0.5);
  
  // BASIC LIGHTNING (Lights calculation)

  vec3 norm = normalize(normal);
  vec3 ldir = normalize(vec3(5.0, 2.0, 5.0) - fpos);

  float diff = max(dot(norm, ldir), 0.0);

  //light color;
  vec3 diffuse = diff * light_color;

  // SPECULAR LIGHT

  float s_strength = 5.0;

  vec3 view_dir = normalize(view_pos - fpos);
  vec3 reflec_dir = reflect(-ldir, norm);

  //--------------------------------------------------Radius
  float spec = pow(max(dot(view_dir, reflec_dir), 0.0), 128);

  vec3 specular = s_strength * spec * light_color;

  frag_color = vec4((ambient + diffuse + specular) * texture( texture_s, vmap ).rgb, 1.0); */
  /* frag_color = vec4(vmap.x, vmap.y, vpos.z ,1.0);} */
}