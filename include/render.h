#pragma once 

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "maths.h"
#include "tile.h"

struct Shader_Program;
struct Sprite;

struct Renderer {
    GLuint vao;
    Shader_Program* shader;
    std::vector<Sprite> sprites;
    int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH];

    Renderer(Shader_Program* shader);
    void draw_sprite(Sprite* sprite);
    void add_sprite(Sprite sprite);
    void set_tilemap(int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH]);
    void draw_tilemap();
    void draw_tile(int tile_x, int tile_y, Tile_Type type);
    void render();
    void clear();
};


