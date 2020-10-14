#pragma once 

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Display {

    extern int width;
    extern int height;
    extern int fps_cap;
    extern double last_frame_time;
    extern double current_frame_time;
    extern float frame_dt;
    extern GLFWwindow* window;

    bool window_should_close();
    void create_window(const char* title, GLFWkeyfun key_callback);
    void update();
    void swap_buffers();
    void close();
    double get_time();
}

