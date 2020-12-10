#include "building.h"
#include "texture.h"
#include "input.h"
#include "render.h"

void init_buildings(Array<Building> *buildings, Renderer *renderer) {
    Building castle1;
    castle1.width = 64;
    castle1.height = 64;
    castle1.position = glm::vec2(100, 350);
    castle1.sprite.texture = load_texture("castle.png");
    array_add(buildings, castle1);

    Building castle2;
    castle2.width = 64;
    castle2.height = 64;
    castle2.position = glm::vec2(1175, 350);
    castle2.sprite.texture = load_texture("castle.png");
    array_add(buildings, castle2);

    for (auto& building : *buildings) {
        renderer->add_entity(&building);
    }
}

void update_buildings(Array<Building> *buildings, Input *input, double dt) {
    for (auto& building : *buildings) {
        if (input->mouse_over(&building)) {
            // if mouse over building, show highlight and some stats or something
            

            // if building clicked, show building options
            if (input->mouse_pressed(MOUSE_BUTTON_LEFT) && input->mouse_over(&building)) {
                building.show_options = true;
            }
        }
    }
}

