#pragma once

#include "maths.h"
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define NUM_TILE_TYPES  6

enum Tile_Type {
    TILE_GRASS,                // 0
    TILE_GRASS_BLOCK,          // 1
    TILE_DIRT_BLOCK,           // 2
    TILE_BLACK_BLOCK,          // 3
    TILE_PINK,                 // 4
    TILE_GREEN_OUTLINE,        // 5
    COUNT
};

struct Tile {
    GLuint texture;
    Tile(const char* filename);
    Tile() {};
};

struct Tilemap { 
    int origin_x;
    int origin_y;
    int count_x;
    int count_y;
    int tile_width;
    int tile_height;
    int* tiles;
};

// maps tile ids to tile properties
extern Tile tile_types[NUM_TILE_TYPES];

void init_tile_types();

Tile_Type tile_at(Tilemap* tilemap, float x, float y);

bool is_solid(Tile_Type type);

