#include "render.h"
#include "shader_program.h" 
#include "sprite.h" 
#include "display.h" 

// 
// scope file
//
GLuint init_gl_buffers() {

    //  @Cleanup in order to be a good citizen these should be managed
    //  somewhere so that the buffers can be freed when no longer needed. That
    //  is just at the end of the program though so whatever.
    GLuint vao;
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
Renderer::Renderer(Shader_Program* _shader) {
    shader = _shader;
    vao = init_gl_buffers();
    glm::mat4 projection = glm::ortho(0.0f, (float)Display::width, 
                                     (float)Display::height, 0.0f, 
                                     -1.0f, 1.0f);
    start_shader(shader->program_id);
    load_uniform_matrix(shader->loc_projection_matrix, projection);
    stop_shader();
}

void Renderer::add_sprite(Sprite sprite) {
    sprites.push_back(sprite);
}

void Renderer::draw_sprite (Sprite* sprite) 
{
    glm::mat4 matrix = glm::mat4(1.0f);

    // translate
    matrix = glm::translate(matrix, glm::vec3(sprite->position, 0.0f));

    // rotate about center
    matrix = glm::translate(matrix, glm::vec3(0.5f * sprite->width * sprite->scale.x,
                                              0.5f * sprite->height * sprite->scale.y,
                                              0.0f));

    matrix = glm::rotate(matrix, glm::radians(sprite->rotation), 
                         glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::translate(matrix, glm::vec3(-0.5f * sprite->width * sprite->scale.x,
                                              -0.5f * sprite->height * sprite->scale.y,
                                              0.0f));

    // scale
    matrix = glm::scale(matrix, glm::vec3(sprite->width * sprite->scale.x,
                                          sprite->height * sprite->scale.y, 
                                          1.0f));

    // uniforms
    load_uniform_matrix(shader->loc_transformation_matrix, matrix);
    load_uniform_vector3(shader->loc_sprite_color, sprite->color);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);

    // draw
    //
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // all sprites use the same 6 vertices

    // unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Renderer::set_tilemap(int _tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH]) {
    memcpy(tilemap, _tilemap, sizeof(int) * TILEMAP_WIDTH * TILEMAP_HEIGHT);
}

void Renderer::draw_tilemap() {
    for (int j=0; j < TILEMAP_HEIGHT; j++) {
        for (int i=0; i < TILEMAP_WIDTH; i++) {
            Tile_Type type = (Tile_Type)tilemap[j][i];
            draw_tile(i, j, type);
        }
    }
}

void Renderer::draw_tile(int tile_x, int tile_y, Tile_Type type) {
    Tile tile = tile_types[type];

    float pos_x = (tile_x * TILE_WIDTH);
    float pos_y = (tile_y * TILE_HEIGHT);

    // get isometric coords
    float iso_x = 0.5f * (pos_x - pos_y);
    float iso_y = 0.25f * (pos_x + pos_y);
    iso_x += TILEMAP_ORIGIN_X;
    iso_y += TILEMAP_ORIGIN_Y;

    // translate
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, glm::vec3(iso_x, iso_y, 0.0f));
    //matrix = glm::translate(matrix, glm::vec3(pos_x, pos_y, 0.0f));

    //
    // rotation could go here, currently there is none 
    //
    
    // scale
    matrix = glm::scale(matrix, glm::vec3(TILE_WIDTH, TILE_HEIGHT, 0.0f));

    // uniforms
    load_uniform_matrix(shader->loc_transformation_matrix, matrix);
    load_uniform_vector3(shader->loc_sprite_color, glm::vec3(1.0f, 1.0f, 1.0f)); // no color right now

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tile.texture);

    // draw
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // all sprites use the same 6 vertices

    // unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::render() {
    clear();    
    start_shader(shader->program_id);
    draw_tilemap();
    for (auto sprite: sprites) {
        draw_sprite(&sprite);
    }
    stop_shader();
}

// this doesn't really need to be a method on Renderer
void Renderer::clear() {
    //glEnable(GL_DEPTH_TEST);
    glClearColor(59/255.0f, 0/255.0f, 0/255.0f, 1); // red
    //glClearColor(0/255.0f, 0/255.0f, 0/255.0f, 1);  // black
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

