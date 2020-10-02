#pragma once 

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "maths.h"
#include "tile.h"

struct Shader_Program;
struct Sprite;

struct Sprite_Renderer {
    GLuint vao;
    Shader_Program* shader;
    std::vector<Sprite> sprites;

    Sprite_Renderer(Shader_Program* shader);
    void draw_sprite(Sprite* sprite);
    void add_sprite(Sprite sprite);
    void draw_tilemap(int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH]);
    void draw_tile(int tile_x, int tile_y, Tile_Type type);
    void render();
    void clear();
};


