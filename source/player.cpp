#include <algorithm>
#include "player.h"
#include "input.h"
#include "tile.h"
#include "collision.h"

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
    float min_t;
    bool hit = collide_tilemap(tilemap, position, target, hitbox_width, hitbox_height, &min_t);

    if (hit) {
        target = position + (target - position) * min_t;
    }

    position = target;
}

