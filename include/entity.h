#pragma once

#include "maths.h"
#include "sprite.h"

struct Entity {
    glm::vec2 position         = glm::vec2(0.0f, 0.0f);
    float rotation             = 0;
    glm::vec2 scale            = glm::vec2(1.0f, 1.0f);
    float width                = 32;
    float height               = 32;
    float hitbox_width  = 32;
    float hitbox_height = 32;
    Sprite sprite;

    //Player_Id player;

    char *name;
    int cost;
    int sell_value;
    int hp;
    int max_hp;

    bool selected = false;

    //virtual void awake();
    //virtual void start();
    //virtual void update();
    //virtual void on_gui();
    //virtual void perform_action(char *action);

};

