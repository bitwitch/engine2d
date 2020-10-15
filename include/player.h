#pragma once
#include "entity.h"

struct Tilemap;
struct Input;

struct Player : public Entity {
    float speed = 100;
    Tilemap* tilemap;
    void update(Input* input, double dt);
};

