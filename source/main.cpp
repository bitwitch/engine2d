#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "input.h"
#include "tile.h"
#include "player.h"
#include "texture.h"
#include "shader_program.h"
#include "render.h"

int main(int argc, char** argv) 
{
    Display::create_window("Engine 2D");

    Input::init(Display::window);

    Input input = Input();

    init_tile_types();

    Tilemap tilemap;
    tilemap.count_x     = 20;
    tilemap.count_y     = 15;
    tilemap.origin_x    = 600;
    tilemap.origin_y    = 100;
    tilemap.tile_width  = 64;
    tilemap.tile_height = 64;

    int tiles[15][20] = 
    {
        { 6,7,7,6,6, 7,7,7,7,7, 6,6,6,6,6, 6,6,6,6,6 },
        { 6,7,7,7,6, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7 },
        { 6,7,7,7,6, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7 },
        { 6,7,7,7,6, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7 },
        { 6,7,7,7,7, 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7 },
        { 6,7,7,7,7, 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7 },
        { 6,7,7,7,7, 6,7,7,7,7, 7,7,6,6,6, 6,7,7,7,7 },
        { 6,7,7,7,7, 6,7,7,7,7, 7,7,6,7,7, 7,6,7,7,7 },
        { 6,7,7,7,7, 7,6,7,7,7, 6,7,6,7,7, 7,7,6,7,7 },
        { 6,7,7,7,7, 7,6,7,7,7, 6,6,6,7,7, 7,7,7,6,6 },
        { 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,6 },
        { 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,6 },
        { 6,7,7,7,7, 7,7,6,7,7, 7,7,7,7,7, 7,7,7,7,6 },
        { 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,6 },
        { 6,7,7,7,7, 7,7,7,7,7, 7,7,7,7,7, 7,7,7,7,6 }
    };

    //int tiles[15][20] = 
    //{
        //{ 5,5,5,5,5, 5,5,5,5,5, 4,4,4,4,4, 4,4,4,4,4 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        //{ 5,5,5,5,5, 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        //{ 5,5,5,5,5, 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        //{ 5,5,5,5,5, 4,5,5,5,5, 5,5,4,4,4, 4,5,5,5,5 },
        //{ 5,5,5,5,5, 4,5,5,5,5, 5,5,4,5,5, 5,4,5,5,5 },
        //{ 5,5,5,5,5, 5,4,5,5,5, 4,5,4,5,5, 5,5,4,5,5 },
        //{ 5,5,5,5,5, 5,4,5,5,5, 4,4,4,5,5, 5,5,5,4,4 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        //{ 5,5,5,5,5, 5,5,4,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        //{ 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 }
    //};


    tilemap.tiles = (int *)tiles;

    // NOTE(shaw): this could go in the renderer ??
    Shader_Program shader = make_shader("data/shaders/vertex_shader.glsl", 
                                        "data/shaders/fragment_shader.glsl");

    Renderer renderer = Renderer(&shader);

    renderer.tilemap = &tilemap;

    Player player;
    player.width = 32;
    player.height = 32;
    player.move_collision_width = player.width;
    player.move_collision_height = player.height;

    player.position = glm::vec2(100, 100);
    player.sprite.texture = load_texture("player.png");
    player.tilemap = &tilemap;

    renderer.add_entity(&player);

    while (!Display::window_should_close())
    {
        input.update_keyboard(); // needs to happen before Display::update() which polls events

        Display::update();

        player.update(&input, Display::frame_dt);

        renderer.render();

        Display::swap_buffers();
    }

    Display::close();

    exit(EXIT_SUCCESS);
}


