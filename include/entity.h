#pragma once

#include "maths.h"
#include "sprite.h"

struct Entity {
    glm::vec2 position   = glm::vec2(0.0f, 0.0f);
    float rotation       = 0;
    glm::vec2 scale      = glm::vec2(1.0f, 1.0f);
    float width          = 32;
    float height         = 32;
    Sprite sprite;
};


