#pragma once
#include "entity.h"
#include "containers.h"

struct Renderer;
struct Input;


struct Building : public Entity {
    int id;
    int health = 100;
    bool show_options = false;
};


void init_buildings(Array<Building> *buildings, Renderer *renderer);

void update_buildings(Array<Building> *buildings, Input *input, double dt);

