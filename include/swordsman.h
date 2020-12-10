#pragma once
#include "entity.h"

struct Swordsman : public Entity {
    // TODO(shaw): remove the temp default
    glm::vec2 target = glm::vec2(1100, 350);
};

void update_swordsman(Swordsman* sman);

