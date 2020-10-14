#pragma once

#include <GLFW/glfw3.h>

enum Key {
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_P,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_COUNT
};

namespace Input {
    extern bool key_pressed[KEY_COUNT];
    extern bool key_repeated[KEY_COUNT];
    extern bool key_released[KEY_COUNT];

    extern bool keyboard_state[KEY_COUNT];

    void update_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    void update_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
};

