#include "player.h"
#include "input.h"
#include "tile.h"

// TODO(shaw): fix faster speed on diagonals
void Player::update(Input* input, double dt) {

    float target_x = position.x;
    float target_y = position.y;

    // move horizontal
    if (input->key_down(KEY_D)) {
        target_x = position.x + speed * dt;
    }
    if (input->key_down(KEY_A)) {
        target_x = position.x - speed * dt;
    }

    // move vertical
    if (input->key_down(KEY_W)) {
        target_y = position.y - speed * dt;
    }
    if (input->key_down(KEY_S)) {
        target_y = position.y + speed * dt;
    }


    //
    // tilemap collisions
    //

    // keep a 1px border for being against an obstacle and still moving
    float left   = target_x - (0.5 * move_collision_width) + 1;
    float right  = target_x + (0.5 * move_collision_width) - 1;
    float top    = target_y - move_collision_height + 1;
    float bottom = target_y - 1;

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
                // set player target_to the right of the collision tile
                float collision_tile_right = (float)(int)(left / tilemap->tile_width) * tilemap->tile_width + tilemap->tile_width;
                target_x = collision_tile_right + 0.5 * move_collision_width;

                left    = target_x - (0.5 * move_collision_width) + 1;
                right   = target_x + (0.5 * move_collision_width) - 1;
                tile_tl = tile_at(tilemap, left, top);
                tile_bl = tile_at(tilemap, left, bottom);
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
                // set player target_to the left of the collision tile
                float collision_tile_left = (float)(int)(right / tilemap->tile_width) * tilemap->tile_width;
                target_x = collision_tile_left - 0.5 * move_collision_width;

                left    = target_x - (0.5 * move_collision_width) + 1;
                right   = target_x + (0.5 * move_collision_width) - 1;
                tile_tl = tile_at(tilemap, left, top);
                tile_bl = tile_at(tilemap, left, bottom);
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
                // set player target_to the left of the collision tile
                float collision_tile_bottom = (float)(int)(top / tilemap->tile_height) * tilemap->tile_height + tilemap->tile_height;
                target_y = collision_tile_bottom + move_collision_height;

                top     = target_y - move_collision_height + 1;
                bottom  = target_y - 1;
                tile_tr = tile_at(tilemap, right, top);
                tile_tl = tile_at(tilemap, left, top);
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
                // set player target_to the top of the collision tile
                float collision_tile_top = (float)(int)(bottom / tilemap->tile_height) * tilemap->tile_height;
                target_y = collision_tile_top;

                top     = target_y - move_collision_height + 1;
                bottom  = target_y - 1;
                tile_br = tile_at(tilemap, right, bottom);
                tile_bl = tile_at(tilemap, left, bottom);
            }
        }
    }

    position.x = target_x;
    position.y = target_y;
}



