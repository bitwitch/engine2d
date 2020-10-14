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
    Display::create_window("Engine 2D", Input::update_keyboard);

    init_tile_types();

    Tilemap tilemap;
    tilemap.count_x     = 20;
    tilemap.count_y     = 15;
    tilemap.origin_x    = 0;
    tilemap.origin_y    = 0;
    tilemap.tile_width  = 64;
    tilemap.tile_height = 64;

    int tiles[15][20] = 
    {
        { 4,5,5,4,4, 5,5,5,5,5, 4,4,4,4,4, 4,4,4,4,4 },
        { 4,5,5,5,4, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        { 4,5,5,5,4, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        { 4,5,5,5,4, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        { 4,5,5,5,5, 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        { 4,5,5,5,5, 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5 },
        { 4,5,5,5,5, 4,5,5,5,5, 5,5,4,4,4, 4,5,5,5,5 },
        { 4,5,5,5,5, 4,5,5,5,5, 5,5,4,5,5, 5,4,5,5,5 },
        { 4,5,5,5,5, 5,4,5,5,5, 4,5,4,5,5, 5,5,4,5,5 },
        { 4,5,5,5,5, 5,4,5,5,5, 4,4,4,5,5, 5,5,5,4,4 },
        { 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        { 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        { 4,5,5,5,5, 5,5,4,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        { 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 },
        { 4,5,5,5,5, 5,5,5,5,5, 5,5,5,5,5, 5,5,5,5,4 }
    };

    tilemap.tiles = (int *)tiles;

    // NOTE(shaw): this could go in the renderer ??
    Shader_Program shader = make_shader("data/shaders/vertex_shader.glsl", 
                                        "data/shaders/fragment_shader.glsl");

    Renderer renderer = Renderer(&shader);

    renderer.tilemap = &tilemap;

    Player player;
    player.width = 100;
    player.height = 134;
    player.position = glm::vec2(100, 100);
    player.sprite.texture = load_texture("nezuko.png");
    player.tilemap = &tilemap;

    renderer.add_entity(&player);


    Tile_Type tile = tile_at(&tilemap, 50, 50);
    printf("tile at 50, 50: %d\n", tile);


    while (!Display::window_should_close())
    {
        Display::update();

        player.update(Display::frame_dt);

        renderer.render();

        Display::swap_buffers();
    }

    Display::close();

    exit(EXIT_SUCCESS);
}


