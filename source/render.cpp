#include "render.h"

// 
// scope file
//
GLuint init_gl_buffers() {
    GLuint vao;
    GLuint vbo;

    GLfloat vertices[] = {
        // pos       // tex
        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 0.0f, 
    
        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 1.0f,  1.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glEnableVertexAtrribArray(0);
    glVertexAtrribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

//
// scope export
//
Sprite_Renderer::Sprite_Renderer(ShaderProgram* _shader) {
    shader = _shader;
    vao = init_gl_buffers();
}


void Sprite_Renderer::draw_sprite (Sprite* sprite) {
    shader->start();

    Matrix4 transformation_matrix = Matrix4();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    shader->stop();
}






