#include "input.h"
#include <map>

// scope file
std::map<int, Key> key_glfw_to_native = {
    {GLFW_KEY_ESCAPE, KEY_ESCAPE},
    {GLFW_KEY_SPACE, KEY_SPACE},
    {GLFW_KEY_W, KEY_W},
    {GLFW_KEY_A, KEY_A},
    {GLFW_KEY_S, KEY_S},
    {GLFW_KEY_D, KEY_D},
    {GLFW_KEY_P, KEY_P}
};

// scope export

namespace Input { 

bool key_pressed[KEY_COUNT]  = {};
bool key_repeated[KEY_COUNT] = {};
bool key_released[KEY_COUNT] = {};

bool keyboard_state[KEY_COUNT] = {};

void update_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::map<int, Key>::iterator it = key_glfw_to_native.find(key);
    if (it == key_glfw_to_native.end())
        return;
        
    Key input_key = it->second;

    switch(action) {
    case GLFW_PRESS:
        key_pressed[input_key]  = true; 
        break;
    case GLFW_REPEAT:
        key_repeated[input_key] = true; 
        break;
    case GLFW_RELEASE:
        key_released[input_key] = true; 
        break;
    }


    // TODO: TEMPORARY: DELETE ME!!!!! PUT ME WHERE I BELONG!! ARE YOU MY DADDY??
    // TODO: TEMPORARY: DELETE ME!!!!! PUT ME WHERE I BELONG!! ARE YOU MY DADDY??
    // TODO: TEMPORARY: DELETE ME!!!!! PUT ME WHERE I BELONG!! ARE YOU MY DADDY??
    if (key_pressed[KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

}
