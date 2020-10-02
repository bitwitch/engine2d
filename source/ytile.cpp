#include "tile.h"

//
// scope file
//


//
// scope export
//
Tile tile_types[NUM_TILE_TYPES];

void init_tile_types() {
    Tile tile_grey  = make_tile(0, glm::vec3(0.5f, 0.5f, 0.5f));
    Tile tile_white = make_tile(1, glm::vec3(1.0f, 1.0f, 1.0f));

    tile_types[0] = tile_grey;
    tile_types[0] = tile_white;
}

Tile make_tile(int id, glm::vec3 color) {
    Tile result;
    result.id = id;
    result.color = color;
    return result;
}

void draw_tilemap(int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH]) {
    for (int j=0; j<TILEMAP_HEIGHT; j++) {
        for (int i=0; i<TILEMAP_WIDTH; i++) {
            int id = tilemap[j][i];
            Tile tile = tile_types[id];

        }
    }
}

