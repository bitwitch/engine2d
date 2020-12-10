#include "input.h"
#include "entity.h"
#include <map>


// scope file
namespace {
    std::map<int, Key> key_glfw_to_native = {
        {GLFW_KEY_ESCAPE, KEY_ESCAPE},
        {GLFW_KEY_SPACE, KEY_SPACE},
        {GLFW_KEY_W, KEY_W},
        {GLFW_KEY_A, KEY_A},
        {GLFW_KEY_S, KEY_S},
        {GLFW_KEY_D, KEY_D},
        {GLFW_KEY_P, KEY_P}
    };

    std::map<int, Mouse_Button> mouse_button_glfw_to_native = {
        {GLFW_MOUSE_BUTTON_LEFT, MOUSE_BUTTON_LEFT},
        {GLFW_MOUSE_BUTTON_RIGHT, MOUSE_BUTTON_RIGHT}
    };
}

// scope export
std::vector<Input*> Input::instances;

Input::Input() {
    for (int i=0; i<KEY_COUNT; i++) {
        keyboard_state[i]      = STILL_RELEASED;
        last_keyboard_state[i] = STILL_RELEASED;
    }
    for (int i=0; i<MOUSE_BUTTON_COUNT; i++) {
        mouse_button_state[i]      = STILL_RELEASED;
        last_mouse_button_state[i] = STILL_RELEASED;
    }
    instances.push_back(this);
}

void Input::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

// KEYBOARD
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::map<int, Key>::iterator it = key_glfw_to_native.find(key);
    if (it == key_glfw_to_native.end())
        return;
        
    Key input_key = it->second;

    for (Input* input: instances) {
        if (action == GLFW_PRESS) {
            input->keyboard_state[input_key] = JUST_PRESSED;

        } else if (action == GLFW_REPEAT) {
            input->keyboard_state[input_key] = STILL_PRESSED;

        } else if (action == GLFW_RELEASE) {
            input->keyboard_state[input_key] = JUST_RELEASED;

        }
    }
}

void Input::update_keyboard() {
    for (int i=0; i<KEY_COUNT; i++) {
        switch(keyboard_state[i]) {
        case JUST_PRESSED:
            keyboard_state[i] = STILL_PRESSED;
            break;
        case JUST_RELEASED:
            keyboard_state[i] = STILL_RELEASED;
            break;
        default: 
            break;
        }
    }
}

bool Input::key_down(Key key) {
    return keyboard_state[key] == JUST_PRESSED ||
           keyboard_state[key] == STILL_PRESSED;
}

bool Input::key_pressed(Key key) {
    return keyboard_state[key] == JUST_PRESSED;
}

// MOUSE
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    for (Input* input: instances) {
        input->mouse_x = xpos;
        input->mouse_y = ypos;
    }
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    std::map<int, Mouse_Button>::iterator it = mouse_button_glfw_to_native.find(button);
    if (it == mouse_button_glfw_to_native.end())
        return;
        
    Mouse_Button input_button = it->second;

    for (Input* input: instances) {
        if (action == GLFW_PRESS) {
            input->mouse_button_state[input_button] = JUST_PRESSED;

        } else if (action == GLFW_REPEAT) {
            input->mouse_button_state[input_button] = STILL_PRESSED;

        } else if (action == GLFW_RELEASE) {
            input->mouse_button_state[input_button] = JUST_RELEASED;

        }
    }
}


void Input::update_mouse() {
     for (int i=0; i<MOUSE_BUTTON_COUNT; i++) {
        switch(mouse_button_state[i]) 
        {
        case JUST_PRESSED:
            mouse_button_state[i] = STILL_PRESSED;
            break;
        case JUST_RELEASED:
            mouse_button_state[i] = STILL_RELEASED;
            break;
        default: 
            break;
        }
    }   
}

bool Input::mouse_down(Mouse_Button mouse_button) {
    return mouse_button_state[mouse_button] == JUST_PRESSED ||
           mouse_button_state[mouse_button] == STILL_PRESSED;
}

bool Input::mouse_pressed(Mouse_Button mouse_button) {
    return mouse_button_state[mouse_button] == JUST_PRESSED;
}

bool Input::mouse_over(Entity *entity) {
    if (mouse_x >= entity->position.x - 0.5f * entity->width && 
        mouse_x <= entity->position.x + 0.5f * entity->width &&        
        mouse_y >= entity->position.y - 0.5f * entity->height && 
        mouse_y <= entity->position.y + 0.5f * entity->height) 
    {
        return true;
    }
    return false;
}


