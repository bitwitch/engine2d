#pragma once
#include "maths.h"
#include "entity.h"



struct Sprite : public Entity {
    GLuint texture = 0;
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};


