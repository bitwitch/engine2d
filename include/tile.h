#pragma once

#include "maths.h"
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define TILE_WIDTH     64
#define TILE_HEIGHT    64
#define TILEMAP_WIDTH  20
#define TILEMAP_HEIGHT 15

#define TILEMAP_ORIGIN_X  500
#define TILEMAP_ORIGIN_Y  50

#define NUM_TILE_TYPES  6

enum Tile_Type {
    TILE_GRASS,
    TILE_GRASS_BLOCK,
    TILE_DIRT_BLOCK,
    TILE_BLACK_BLOCK,
    TILE_PINK,
    TILE_GREEN_OUTLINE,
    COUNT
};

struct Tile {
    GLuint texture;
    Tile(const char* filename);
    Tile() {};
};

// maps tile ids to tile properties
extern Tile tile_types[NUM_TILE_TYPES];

void init_tile_types();


