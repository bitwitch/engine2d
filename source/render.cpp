#include "render.h"
#include "shader_program.h" 
#include "entity.h" 
#include "display.h" 

// 
// scope file
//
GLuint init_gl_buffers() {

    //  @Cleanup in order to be a good citizen these should be managed
    //  somewhere so that the buffers can be freed when no longer needed. 
    //  Right now that is just at the end of the program though so whatever.
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

void Renderer::add_entity(Entity* entity) {
    entities.push_back(entity);
}

void Renderer::draw_entity (Entity* entity)
{
    glm::mat4 matrix = glm::mat4(1.0f);

    // draw coords, entity pos is considered its center
    float draw_x = entity->position.x - (0.5f * entity->width  * entity->scale.x);
    float draw_y = entity->position.y - (0.5f * entity->height * entity->scale.y);

    // get isometric coords
    //float iso_x = 0.5f * (draw_x - draw_y);
    //float iso_y = 0.25f * (draw_x + draw_y);
    //iso_x += tilemap->origin_x;
    //iso_y += tilemap->origin_y;

    // translate
    matrix = glm::translate(matrix, glm::vec3(draw_x, draw_y, 0.0f));
    //matrix = glm::translate(matrix, glm::vec3(iso_x, iso_y, 0.0f));


    // rotate about center
    matrix = glm::translate(matrix, glm::vec3(0.5f * entity->width * entity->scale.x,
                                              0.5f * entity->height * entity->scale.y,
                                              0.0f));

    matrix = glm::rotate(matrix, glm::radians(entity->rotation), 
                         glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::translate(matrix, glm::vec3(-0.5f * entity->width * entity->scale.x,
                                              -0.5f * entity->height * entity->scale.y,
                                              0.0f));

    // scale
    matrix = glm::scale(matrix, glm::vec3(entity->width * entity->scale.x,
                                          entity->height * entity->scale.y, 
                                          0.0f));

    // uniforms
    load_uniform_matrix(shader->loc_transformation_matrix, matrix);
    load_uniform_vector3(shader->loc_sprite_color, entity->sprite.color);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->sprite.texture);

    // draw
    //
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // all sprites use the same 6 vertices

    // unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_tilemap() {
    for (int j=0; j < tilemap->count_y; j++) {
        for (int i=0; i < tilemap->count_x; i++) {
            Tile_Type type = (Tile_Type)tilemap->tiles[j * tilemap->count_x + i];
            draw_tile(i, j, type);
        }
    }
}

void Renderer::draw_tile(int tile_x, int tile_y, Tile_Type type) {
    Tile tile = tile_types[type];

    float pos_x = (tile_x * tilemap->tile_width);
    float pos_y = (tile_y * tilemap->tile_height);

    // get isometric coords
    float iso_x = 0.5f * (pos_x - pos_y);
    float iso_y = 0.25f * (pos_x + pos_y);
    iso_x += tilemap->origin_x;
    iso_y += tilemap->origin_y;

    // translate
    glm::mat4 matrix = glm::mat4(1.0f);
    //matrix = glm::translate(matrix, glm::vec3(iso_x, iso_y, 0.0f));
    matrix = glm::translate(matrix, glm::vec3(pos_x, pos_y, 0.0f));

    //
    // rotation could go here, currently there is none 
    //
    
    // scale
    matrix = glm::scale(matrix, glm::vec3(tilemap->tile_width, tilemap->tile_height, 0.0f));

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
    for (auto entity: entities) {
        draw_entity(entity);
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

