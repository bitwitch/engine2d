#include "collision.h"
#include "tile.h"


// returns true on a tile collision, false otherwise
// if there is a collision, t will be set to the normalized distance along
// the line from position to target where a collision with a tile occured
bool collide_tilemap(Tilemap *tilemap, glm::vec2 position, glm::vec2 target, float hitbox_width, float hitbox_height, float *t) 
{
 
    float min_x = std::fmin(position.x, target.x);
    float min_y = std::fmin(position.y, target.y);
    float max_x = std::fmax(position.x, target.x);
    float max_y = std::fmax(position.y, target.y);

    int min_tile_x = (int)((min_x - (0.5f*hitbox_width))  / tilemap->tile_width);
    int min_tile_y = (int)((min_y - (0.5f*hitbox_height)) / tilemap->tile_height);
    int max_tile_x = (int)((max_x + (0.5f*hitbox_width))  / tilemap->tile_width);
    int max_tile_y = (int)((max_y + (0.5f*hitbox_height)) / tilemap->tile_height);

    // tile corner positions, relative to tile center, adjusted by the minkowski sum
    auto top_left     = glm::vec2(-0.5f * (tilemap->tile_width + hitbox_width), -0.5f * (tilemap->tile_height + hitbox_height));
    auto top_right    = glm::vec2( 0.5f * (tilemap->tile_width + hitbox_width), -0.5f * (tilemap->tile_height + hitbox_height));
    auto bottom_left  = glm::vec2(-0.5f * (tilemap->tile_width + hitbox_width),  0.5f * (tilemap->tile_height + hitbox_height));
    auto bottom_right = glm::vec2( 0.5f * (tilemap->tile_width + hitbox_width),  0.5f * (tilemap->tile_height + hitbox_height));

    float min_t = INFINITY;
    for (int tile_y = min_tile_y; tile_y <= max_tile_y; tile_y++) {
        for (int tile_x = min_tile_x; tile_x <= max_tile_x; tile_x++) {
            Tile tile = tile_at(tilemap, tile_x, tile_y);
            if (tile.solid) {
                auto tile_center = glm::vec2(
                    tile_x * tilemap->tile_width + 0.5f * tilemap->tile_width, 
                    tile_y * tilemap->tile_height + 0.5f * tilemap->tile_height);

                // entity position and target, relative to tile center
                glm::vec2 rel_position = position - tile_center;
                glm::vec2 rel_target = target - tile_center;

                float t1 = segment_intersect(rel_position, rel_target, top_left, top_right);
                float t2 = segment_intersect(rel_position, rel_target, top_right, bottom_right);
                float t3 = segment_intersect(rel_position, rel_target, bottom_left, bottom_right);
                float t4 = segment_intersect(rel_position, rel_target, top_left, bottom_left);

                if (t1 == -1.0f && t2 == -1.0f && t3 == -1.0f && t4 == -1.0f) continue;

                if (t1 == -1.0f) t1 = INFINITY; 
                if (t2 == -1.0f) t2 = INFINITY;
                if (t3 == -1.0f) t3 = INFINITY; 
                if (t4 == -1.0f) t4 = INFINITY;

                min_t = std::fmin(min_t, std::fmin(std::fmin(t1, t2), std::fmin(t3, t4)));
             }
        }
    }

    if (min_t == INFINITY) {
        return false;
    }

    *t = min_t;
    return true;
}
