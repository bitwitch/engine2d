#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

struct Entity;

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

enum Mouse_Button {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_COUNT,
};

enum Press_State { 
    JUST_PRESSED,
    STILL_PRESSED,
    JUST_RELEASED,
    STILL_RELEASED,
    PRESS_STATE_COUNT
};

struct Input {
    double mouse_x;
    double mouse_y;

    Press_State mouse_button_state[MOUSE_BUTTON_COUNT];
    Press_State last_mouse_button_state[MOUSE_BUTTON_COUNT];

    Press_State keyboard_state[KEY_COUNT];
    Press_State last_keyboard_state[KEY_COUNT];

    void update_keyboard();
    bool key_down(Key key);
    bool key_pressed(Key key);

    void update_mouse();
    bool mouse_down(Mouse_Button button);
    bool mouse_pressed(Mouse_Button button);
    bool mouse_over(Entity *entity);

    Input();

    static void init(GLFWwindow* window); // registers glfw key callback

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static std::vector<Input*> instances;
};


