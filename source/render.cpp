#include "render.h"
#include "shader_program.h" 
#include "sprite.h" 
#include "display.h" 

// 
// scope file
//
GLuint init_gl_buffers() {
    GLuint vao;

    //  @Cleanup in order to be a good citizen these vbo ids should be managed
    //  somewhere so that the buffers can be freed when no longer needed. That
    //  is just at the end of the program though so whatever.
    GLuint vbo1;
    GLuint vbo2;

    GLfloat vertices[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    GLfloat tex_coords[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f, 

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &vbo2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

//
// scope export
//
Sprite_Renderer::Sprite_Renderer(Shader_Program* _shader) {
    shader = _shader;
    vao = init_gl_buffers();
    glm::mat4 projection = glm::ortho(0.0f, (float)Display::width, (float)Display::height, 0.0f, -1.0f, 1.0f);
    start_shader(shader->program_id);
    load_uniform_matrix(shader->loc_transformation_matrix, projection);
    stop_shader();
}

void Sprite_Renderer::draw_sprite (Sprite* sprite) {

    // TEMP
    // TEMP
    // TEMP
    glEnable(GL_DEPTH_TEST);
    glClearColor(59/255.0f, 0/255.0f, 0/255.0f, 1); // red
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // TEMP
    // TEMP
    // TEMP


    start_shader(shader->program_id);

    glm::mat4 matrix = glm::mat4(1.0f);
    // translate
    matrix = glm::translate(matrix, glm::vec3(sprite->position, 0.0f));

    // rotate about center
    matrix = glm::translate(matrix, glm::vec3(sprite->scale.x * 0.5f, sprite->scale.y * 0.5f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(sprite->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::translate(matrix, glm::vec3(sprite->scale.x * -0.5f, sprite->scale.y * -0.5f, 0.0f));

    // scale
    matrix = glm::scale(matrix, glm::vec3(sprite->scale, 0.0f));

    // uniforms
    load_uniform_matrix(shader->loc_transformation_matrix, matrix);
    load_uniform_vector3(shader->loc_sprite_color, sprite->color);

    //glActiveTexture(GL_TEXTURE0);
    // bind texture
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    stop_shader();
}

