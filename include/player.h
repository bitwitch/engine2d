#pragma once
#include "entity.h"

struct Tilemap;

struct Player : public Entity {
    float speed = 100;
    Tilemap* tilemap;
    void update(double dt);
};

