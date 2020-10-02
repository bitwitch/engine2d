#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;

out vec2 pass_tex_coords;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 sprite_color;

void main(void) {
//  vec4 world_position = transform * vec4(10, 10, 0.0, 1.0);
//   gl_Position = projection * world_position;
//  pass_tex_coords = tex_coords;
    gl_Position = position;
}
