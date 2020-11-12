#include <algorithm>
#include "player.h"
#include "input.h"
#include "tile.h"

// TODO(shaw): fix faster speed on diagonals
void Player::update(Input* input, double dt) {

    glm::vec2 target = position;

    // move horizontal
    if (input->key_down(KEY_D)) {
        target.x = position.x + speed * dt;
    }
    if (input->key_down(KEY_A)) {
        target.x = position.x - speed * dt;
    }

    // move vertical
    if (input->key_down(KEY_W)) {
        target.y = position.y - speed * dt;
    }
    if (input->key_down(KEY_S)) {
        target.y = position.y + speed * dt;
    }


    //
    // tilemap collisions
    //

    float min_x = std::fmin(position.x, target.x);
    float min_y = std::fmin(position.y, target.y);
    float max_x = std::fmax(position.x, target.x);
    float max_y = std::fmax(position.y, target.y);

    int min_tile_x = (int)((min_x - (0.5f*hitbox_width))  / tilemap->tile_width);
    int min_tile_y = (int)((min_y - (0.5f*hitbox_height)) / tilemap->tile_height);
    int max_tile_x = (int)((max_x + (0.5f*hitbox_width))  / tilemap->tile_width);
    int max_tile_y = (int)((max_y + (0.5f*hitbox_height)) / tilemap->tile_height);

    // tile corner positions, relative to tile center
    auto top_left     = glm::vec2(-0.5f * (tilemap->tile_width + hitbox_width), -0.5f * (tilemap->tile_height + hitbox_height));
    auto top_right    = glm::vec2( 0.5f * (tilemap->tile_width + hitbox_width), -0.5f * (tilemap->tile_height + hitbox_height));
    auto bottom_left  = glm::vec2(-0.5f * (tilemap->tile_width + hitbox_width),  0.5f * (tilemap->tile_height + hitbox_height));
    auto bottom_right = glm::vec2( 0.5f * (tilemap->tile_width + hitbox_width),  0.5f * (tilemap->tile_height + hitbox_height));

    for (int tile_y = min_tile_y; tile_y <= max_tile_y; tile_y++) {
        for (int tile_x = min_tile_x; tile_x <= max_tile_x; tile_x++) {
            Tile tile = tile_at(tilemap, tile_x, tile_y);
            if (tile.solid) {
                auto tile_center = glm::vec2(
                    tile_x * tilemap->tile_width + 0.5f * tilemap->tile_width, 
                    tile_y * tilemap->tile_height + 0.5f * tilemap->tile_height);

                // player position and target, relative to tile center
                glm::vec2 rel_position = position - tile_center;
                glm::vec2 rel_target = target - tile_center;

                // test four walls for intersection
                glm::vec2 intersect1, intersect2, intersect3, intersect4;
                bool test1 = test_intersect(top_left, top_right, rel_position, rel_target, &intersect1);
                bool test2 = test_intersect(top_right, bottom_right, rel_position, rel_target, &intersect2);
                bool test3 = test_intersect(bottom_left, bottom_right, rel_position, rel_target, &intersect3);
                bool test4 = test_intersect(top_left, bottom_left, rel_position, rel_target, &intersect4);

                if (!test1 && !test2 && !test3 && !test4) continue;

                float t1, t2, t3, t4; 
                t1 = t2 = t3 = t4 = 999; // 999 is just a large value meaning no intersection

                if (test1)
                    t1 = segment_percentage(rel_position, rel_target, intersect1);
                if (test2) 
                    t2 = segment_percentage(rel_position, rel_target, intersect2);
                if (test3)
                    t3 = segment_percentage(rel_position, rel_target, intersect3);
                if (test4)
                    t4 = segment_percentage(rel_position, rel_target, intersect4);

                float min_t = std::fmin(std::fmin(t1, t2), std::fmin(t3, t4));
                
                target = glm::lerp(position, target, min_t);
            }
        }
    }

    position = target;
}



