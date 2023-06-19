#version 460

out vec4 frag_color;

in vec3 fpos;
in vec3 vpos;
in vec2 vmap;

in vec3 normal;
in vec3 view_pos;

uniform sampler2D texture_s;

uniform vec3 light_pos;
uniform vec3 light_color;

void main(){

  // AMBIENT LIGHTING (Global)

  float ambientStrength = 1;
  vec3 ambient = ambientStrength * vec3(0.7, 0.6, 0.3);
  
  // BASIC LIGHTNING (Lights calculation)



  vec3 norm = normalize(normal);
  vec3 ldir = normalize(light_pos - fpos);

  float diff = max(dot(norm, ldir), 0.0);

  //light color;
  vec3 diffuse = diff * light_color;

  // SPECULAR LIGHT

  float s_strength = 5.0;

  vec3 view_dir = normalize(view_pos - fpos);
  vec3 reflec_dir = reflect(-ldir, norm);

  //--------------------------------------------------Radius
  float spec = pow(max(dot(view_dir, reflec_dir), 0.0), 12);

  vec3 specular = s_strength * spec * light_color;

  frag_color = vec4((ambient + diffuse + specular) * texture( texture_s, vmap ).rgb, 1.0);
  /* frag_color = vec4(vmap.x, vmap.y, vpos.z ,1.0);} */
}