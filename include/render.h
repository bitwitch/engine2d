#pragma once 
#include "Maths.h"

struct Sprite_Renderer {
    GLuint vao;
    ShaderProgram* shader;

    Sprite_Renderer(ShaderProgram* shader);
    void draw_sprite(Sprite* sprite);
};

