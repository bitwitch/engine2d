#include "tile.h"
#include "texture.h"
#include <assert.h>

//
// scope file
//


//
// scope export
//
// maps tile ids to tile properties
Tile tile_types[NUM_TILE_TYPES];

void init_tile_types() {
    tile_types[TILE_GRASS]        = Tile("blocks_79.png");
    tile_types[TILE_GRASS_BLOCK]  = Tile("blocks_1.png");
    tile_types[TILE_DIRT_BLOCK]   = Tile("blocks_100.png");
    tile_types[TILE_BLACK_BLOCK]  = Tile("blocks_19.png");

    tile_types[TILE_PINK]           = Tile("pink.png");
    tile_types[TILE_GREEN_OUTLINE]  = Tile("green_outline.png");
};

Tile::Tile(const char* filename) {
    texture = load_texture(filename);
}

Tile_Type tile_at(Tilemap* tilemap, float x, float y) {
    int tile_x = (int)(x / tilemap->tile_width);
    int tile_y = (int)(y / tilemap->tile_height);
    int tile_index = tile_y * tilemap->count_x + tile_x;
    assert(tile_index < tilemap->count_x * tilemap->count_y);
    return (Tile_Type)tilemap->tiles[tile_index];
}

bool is_solid(Tile_Type type) {
    return false;
}

