#include "tile.h"
#include "texture.h"

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

    tile_types[TILE_PINK]  = Tile("pink.png");
    tile_types[TILE_GREEN_OUTLINE]  = Tile("green_outline.png");
};

Tile::Tile(const char* filename) {
    texture = load_texture(filename);
}


