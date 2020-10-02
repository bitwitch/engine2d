#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "tile.h"
#include "sprite.h"
#include "texture.h"
#include "shader_program.h"
#include "render.h"

int main(int argc, char** argv) 
{
    Display::create_window("Engine 2D");

    init_tile_types();

    int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH] = 
    {
        { 3,0,0,3,3, 0,0,0,0,0, 3,3,3,3,3, 3,3,3,3,3 },
        { 3,0,0,0,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        { 3,0,0,0,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        { 3,0,0,0,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        { 3,0,0,0,0, 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },

        { 3,0,0,0,0, 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        { 3,0,0,0,0, 3,0,0,0,0, 0,0,3,3,3, 3,0,0,0,0 },
        { 3,0,0,0,0, 3,0,0,0,0, 0,0,3,0,0, 0,3,0,0,0 },
        { 3,0,0,0,0, 0,3,0,0,0, 3,0,3,0,0, 0,0,3,0,0 },
        { 3,0,0,0,0, 0,3,0,0,0, 3,3,3,0,0, 0,0,0,3,3 },

        { 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,3 },
        { 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,3 },
        { 3,0,0,0,0, 0,0,3,0,0, 0,0,0,0,0, 0,0,0,0,3 },
        { 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,3 },
        { 3,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,3 }
    };


    // NOTE(shaw): this could go in the sprite renderer ??
    Shader_Program shader = make_shader("data/shaders/vertex_shader.glsl", 
                                        "data/shaders/fragment_shader.glsl");

    Sprite sprite;
    sprite.width = 64;
    sprite.height = 64;
    sprite.position = glm::vec2(100, 100);
    sprite.texture = load_texture("tanjirou.png");

    Sprite sprite2;
    sprite2.width = 200;
    sprite2.height = 268;
    sprite2.position = glm::vec2(300, 300);
    sprite2.texture = load_texture("nezuko.png");

    Renderer renderer = Renderer(&shader);
    renderer.set_tilemap(tilemap);

    //renderer.add_sprite(sprite);
    //renderer.add_sprite(sprite2);

    while (!Display::window_should_close())
    {
        Display::update();

        renderer.render();

        Display::swap_buffers();
    }

    Display::close();

    exit(EXIT_SUCCESS);
}


