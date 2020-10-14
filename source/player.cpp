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
    //Tile tile = tile_at(x, y);
}


