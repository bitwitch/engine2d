#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "maths.h"

struct Shader_Program {
    GLuint program_id;
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLint loc_transformation_matrix;
    GLint loc_projection_matrix;
    GLint loc_view_matrix;
    GLint loc_sprite_color;
};

Shader_Program make_shader(const char* vert_path, const char* frag_path);
void delete_shader(Shader_Program* p);

void load_uniform_float(GLint location, GLfloat value);
void load_uniform_vector3(GLint location, glm::vec3 vector);
void load_uniform_matrix(GLint location, const glm::mat4 matrix);

void start_shader(GLuint program_id);
void stop_shader();
