#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

struct ShaderProgram {
    GLuint program_id;
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLint loc_transformation_matrix;
    GLint loc_projection_matrix;
    GLint loc_view_matrix;
};

ShaderProgram make_shader(const char* vert_path, const char* frag_path);
void delete_shader(ShaderProgram* p);

void load_uniform_float(ShaderProgram* p, GLuint location, GLfloat value);
void load_uniform_vector(ShaderProgram* p, GLuint location, glm::vec3 vector);
void load_uniform_bool(ShaderProgram* p, GLuint location, bool value);
void load_uniform_matrix(ShaderProgram* p, GLuint location, const glm::mat4& matrix);

void start_shader(GLuint program_id);
void stop_shader();

