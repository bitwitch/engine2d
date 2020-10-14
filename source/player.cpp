#include "player.h"
#include "input.h"
#include "tile.h"

// TODO(shaw): fix faster speed on diagonals
void Player::update(double dt) {
    // move horizontal
    if (Input::key_pressed[KEY_D] || Input::key_repeated[KEY_D]) {
        position.x += speed * dt;
    }
    if (Input::key_pressed[KEY_A] || Input::key_repeated[KEY_A]) {
        position.x -= speed * dt;
    }

    // move vertical
    if (Input::key_pressed[KEY_W] || Input::key_repeated[KEY_W]) {
        position.y -= speed * dt;
    }
    if (Input::key_pressed[KEY_S] || Input::key_repeated[KEY_S]) {
        position.y += speed * dt;
    }

    // tile collisions
    // check the players four corners for tilemap collisions
    float left   = position.x - 0.5 * width;
    float right  = position.x + 0.5 * width;
    float top    = position.y - height;
    float bottom = position.y;

    // top left
    Tile_Type tile_tl = tile_at(tilemap, left, top);
    // top right
    Tile_Type tile_tr = tile_at(tilemap, right, top);
    // bottom left
    Tile_Type tile_bl = tile_at(tilemap, left, bottom);
    // bottom right
    Tile_Type tile_br = tile_at(tilemap, right, bottom);

    printf("D Key Pressed: %d\n", Input::key_pressed[KEY_D]);

    if (Input::key_pressed[KEY_P]) 
        printf("Top Left: %d\nTop Right: %d\nBottom Left: %d\nBottom Right: %d\n", 
                tile_tl, tile_tr, tile_bl, tile_br);
    

}



