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
Tile tile_types[TILE_TYPE_COUNT];

void init_tile_types() {
    tile_types[TILE_GRASS]        = Tile("blocks_79.png");
    tile_types[TILE_GRASS_BLOCK]  = Tile("blocks_1.png");
    tile_types[TILE_DIRT_BLOCK]   = Tile("blocks_100.png");
    tile_types[TILE_BLACK_BLOCK]  = Tile("blocks_19.png");

    tile_types[TILE_PINK]           = Tile("pink.png");
    tile_types[TILE_GREEN_OUTLINE]  = Tile("green_outline.png", false);
    tile_types[TILE_BLACK]          = Tile("black.png");
    tile_types[TILE_WHITE]          = Tile("white.png", false);
}

Tile::Tile(const char* filename, bool _solid) {
    texture = load_texture(filename);
    solid = _solid;
}

Tile tile_at(Tilemap* tilemap, float x, float y) {
    int tile_x = (int)(x / tilemap->tile_width);
    int tile_y = (int)(y / tilemap->tile_height);
    int tile_index = tile_y * tilemap->count_x + tile_x;

    assert(tile_index < tilemap->count_x * tilemap->count_y);
    assert(tile_index >= 0);

    Tile_Type type = (Tile_Type)tilemap->tiles[tile_index];
    return tile_types[type];
}

Tile_Type tile_type_at(Tilemap* tilemap, float x, float y) {
    int tile_x = (int)(x / tilemap->tile_width);
    int tile_y = (int)(y / tilemap->tile_height);
    int tile_index = tile_y * tilemap->count_x + tile_x;

    assert(tile_index < tilemap->count_x * tilemap->count_y);
    assert(tile_index >= 0);

    return (Tile_Type)tilemap->tiles[tile_index];
}
