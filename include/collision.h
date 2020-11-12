#pragma once

#include "glm_subset.h"

struct Tilemap;

// returns true on a tile collision, false otherwise
// if there is a collision, t will be set to the normalized distance along
// the line from position to target where a collision with a tile occured
bool collide_tilemap(Tilemap *tilemap, glm::vec2 position, glm::vec2 target, float hitbox_width, float hitbox_height, float *t);


