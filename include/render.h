#pragma once 

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "maths.h"

struct Shader_Program;
struct Sprite;

struct Sprite_Renderer {
    GLuint vao;
    Shader_Program* shader;
    std::vector<Sprite> sprites;

    Sprite_Renderer(Shader_Program* shader);
    void draw_sprite(Sprite* sprite);
    void add_sprite(Sprite sprite);
    void render();
    void clear();
};


