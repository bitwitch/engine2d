#pragma once

#include "maths.h"
#include <stdio.h>

#define TILE_WIDTH     32
#define TILE_HEIGHT    32
#define TILEMAP_WIDTH  20
#define TILEMAP_HEIGHT 15
#define NUM_TILE_TYPES  2

struct Tile {
    int id;           
    glm::vec3 color;
    // later this will have an image associated as well
};

Tile make_tile(int id, glm::vec3 color);

extern Tile tile_types[NUM_TILE_TYPES];

void init_tile_types();

void draw_tilemap(int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH]);

