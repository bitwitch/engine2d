#pragma once

#include "maths.h"
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

enum Tile_Type {
    TILE_EMPTY,                // 0
    TILE_GRASS,                // 1
    TILE_GRASS_BLOCK,          // 2
    TILE_DIRT_BLOCK,           // 3
    TILE_BLACK_BLOCK,          // 4

    TILE_PINK,                 // 5
    TILE_GREEN_OUTLINE,        // 6
    TILE_BLACK,                // 7
    TILE_WHITE,                // 8
    TILE_TYPE_COUNT
};

struct Tile {
    GLuint texture;
    bool solid;
    Tile(const char* filename, bool solid = true);
    Tile() { solid = false; };
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

// maps tile ids to tile properties, this is the list of all tiles that exist
extern Tile tile_types[TILE_TYPE_COUNT];

void init_tile_types();

// get tile from a world x and y position
Tile tile_at(Tilemap* tilemap, float x, float y);

// get tile from a tilemap column index and row index
Tile tile_at(Tilemap* tilemap, int col, float row);

Tile_Type tile_type_at(Tilemap* tilemap, float x, float y);

