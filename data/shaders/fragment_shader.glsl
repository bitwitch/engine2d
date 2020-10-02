#version 330

in vec2 pass_tex_coords;

uniform sampler2D texture_sampler;
uniform vec3 sprite_color;

out vec4 out_color;

void main(void) {
  vec4 texture_color = texture(texture_sampler, pass_tex_coords);
  if (texture_color.a < 0.2) {
    discard;
  }
  out_color = vec4(sprite_color, 1.0) * texture_color;
}
