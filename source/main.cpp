#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "tile.h"
#include "sprite.h"
#include "shader_program.h"
#include "render.h"

int main(int argc, char** argv) 
{
    Display::create_window("Engine 2D");

    //init_tile_types();

    //int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH] = 
    //{
        //{ 1,0,0,1,1, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1 },
        //{ 1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        //{ 1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        //{ 1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        //{ 1,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },

        //{ 1,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
        //{ 1,0,0,0,0, 1,0,0,0,0, 0,0,1,1,1, 1,0,0,0,0 },
        //{ 1,0,0,0,0, 1,0,0,0,0, 0,0,1,0,0, 0,1,0,0,0 },
        //{ 1,0,0,0,0, 0,1,0,0,0, 1,0,1,0,0, 0,0,1,0,0 },
        //{ 1,0,0,0,0, 0,1,0,0,0, 1,1,1,0,0, 0,0,0,1,1 },

        //{ 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1 },
        //{ 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1 },
        //{ 1,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,1 },
        //{ 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1 },
        //{ 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1 }
    //};


    // NOTE(shaw): this could go in the sprite renderer ??
    Shader_Program shader = make_shader("data/shaders/vertex_shader.glsl", 
                                        "data/shaders/fragment_shader.glsl");

    Sprite sprite;
    sprite.width = 32;
    sprite.height = 32;
    sprite.position = glm::vec2(100, 100);
    sprite.color = glm::vec3(0.3f, 0.2f, 0.7f);

    Sprite sprite2;
    sprite2.width = 32;
    sprite2.height = 32;
    sprite2.position = glm::vec2(600, 500);
    sprite2.color = glm::vec3(0.0f, 0.8f, 0.27f);


    Sprite_Renderer renderer = Sprite_Renderer(&shader);
    renderer.add_sprite(sprite);
    renderer.add_sprite(sprite2);

    while (!Display::window_should_close())
    {
        Display::update();

        //draw_tilemap(tilemap);

        renderer.render();

        Display::swap_buffers();
    }

    Display::close();

    exit(EXIT_SUCCESS);
}


