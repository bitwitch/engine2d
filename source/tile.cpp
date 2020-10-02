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
    tile_types[TILE_GRASS] = Tile("grass.png");
    tile_types[TILE_DIRT]  = Tile("dirt.png");
};

Tile::Tile(const char* filename) {
    texture = load_texture(filename);
}


