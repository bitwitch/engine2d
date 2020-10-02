#pragma once

#include "maths.h"
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define TILE_WIDTH     32
#define TILE_HEIGHT    32
#define TILEMAP_WIDTH  20
#define TILEMAP_HEIGHT 15
#define NUM_TILE_TYPES  2

enum Tile_Type {
    TILE_GRASS,
    TILE_DIRT,
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


