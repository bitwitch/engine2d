#pragma once
#include "entity.h"

struct Tilemap;
struct Input;

struct Player : public Entity {
    float speed = 200;
    float move_collision_width;
    float move_collision_height;
    Tilemap* tilemap;
    void update(Input* input, double dt);
};

