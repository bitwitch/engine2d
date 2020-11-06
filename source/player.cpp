#include "player.h"
#include "input.h"
#include "tile.h"

// TODO(shaw): fix faster speed on diagonals
void Player::update(Input* input, double dt) {

    // move horizontal
    if (input->key_down(KEY_D)) {
        position.x += speed * dt;
    }
    if (input->key_down(KEY_A)) {
        position.x -= speed * dt;
    }

    // move vertical
    if (input->key_down(KEY_W)) {
        position.y -= speed * dt;
    }
    if (input->key_down(KEY_S)) {
        position.y += speed * dt;
    }

    // tile collisions
    // check the players four corners for tilemap collisions
    float left   = position.x - 0.5 * width;
    float right  = position.x + 0.5 * width;
    float top    = position.y - height;
    float bottom = position.y;

    // top left
    Tile tile_tl = tile_at(tilemap, left, top);
    // top right
    Tile tile_tr = tile_at(tilemap, right, top);
    // bottom left
    Tile tile_bl = tile_at(tilemap, left, bottom);
    // bottom right
    Tile tile_br = tile_at(tilemap, right, bottom);


    // collision left
    if (tile_tl.solid || tile_bl.solid) {
        // if player moving left
        if (input->key_down(KEY_A)) {
            // if tile to right of collision tile is not solid
            Tile next_right_top = tile_at(tilemap, left + (float)tilemap->tile_width, top);
            Tile next_right_bottom = tile_at(tilemap, left + (float)tilemap->tile_width, bottom);
            if ((tile_tl.solid && !next_right_top.solid) || (tile_bl.solid && !next_right_bottom.solid)) {
                // set player position to the right of the collision tile
                float collision_tile_right = (float)(int)(left / tilemap->tile_width) * tilemap->tile_width + tilemap->tile_width;
                position.x = collision_tile_right + 0.5 * width;
            }
        }
    }

    // collision right
    if (tile_tr.solid || tile_br.solid) {
        // if player moving right
        if (input->key_down(KEY_D)) {
            // if tile to left of collision tile is not solid
            Tile next_left_top = tile_at(tilemap, right - (float)tilemap->tile_width, top);
            Tile next_left_bottom = tile_at(tilemap, right - (float)tilemap->tile_width, bottom);
            if ((tile_tr.solid && !next_left_top.solid) || (tile_br.solid && !next_left_bottom.solid)) {
                // set player position to the left of the collision tile
                float collision_tile_left = (float)(int)(right / tilemap->tile_width) * tilemap->tile_width;
                position.x = collision_tile_left - 0.5 * width;
            }
        }
    }

    // collision top
    if (tile_tl.solid || tile_tr.solid) {
        // if player moving up
        if (input->key_down(KEY_W)) {
            // if tile to bottom of collision tile is not solid
            Tile next_left_bottom = tile_at(tilemap, left, top + (float)tilemap->tile_height);
            Tile next_right_bottom = tile_at(tilemap, right, top + (float)tilemap->tile_height);
            if ((tile_tl.solid && !next_left_bottom.solid) || (tile_tr.solid && !next_right_bottom.solid)) {
                // set player position to the left of the collision tile
                float collision_tile_bottom = (float)(int)(top / tilemap->tile_height) * tilemap->tile_height + tilemap->tile_height;
                position.y = collision_tile_bottom + height;
            }
        }
    }


    // collision bottom
    if (tile_bl.solid || tile_br.solid) {
        // if player moving up
        if (input->key_down(KEY_S)) {
            // if tile to top of collision tile is not solid
            Tile next_left_top = tile_at(tilemap, left, top - (float)tilemap->tile_height);
            Tile next_right_top = tile_at(tilemap, right, top - (float)tilemap->tile_height);
            if ((tile_bl.solid && !next_left_top.solid) || (tile_br.solid && !next_right_top.solid)) {
                // set player position to the top of the collision tile
                float collision_tile_top = (float)(int)(bottom / tilemap->tile_height) * tilemap->tile_height;
                position.y = collision_tile_top;
            }
        }
    }





















}



