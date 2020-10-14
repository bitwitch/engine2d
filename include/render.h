#pragma once 

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "maths.h"
#include "tile.h"

struct Shader_Program;
struct Entity;

struct Renderer {
    GLuint vao;
    Shader_Program* shader;

    std::vector<Entity*> entities;

    Tilemap* tilemap;

    Renderer(Shader_Program* shader);
    void draw_entity(Entity* entity);
    void add_entity(Entity* entity);
    void draw_tilemap();
    void draw_tile(int tile_x, int tile_y, Tile_Type type);
    void render();
    void clear();
};


