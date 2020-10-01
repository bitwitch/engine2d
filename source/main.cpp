#include <stdlib.h>
#include <stdio.h>
#include "Display.h"

int main(int argc, char** argv) 
{
    Display::create_window("Engine 2D");

    //Loader loader = Loader();

    while (!Display::window_should_close())
    {
        Display::update();

        //renderer.render(light, camera);

        Display::swap_buffers();

    }

    //loader.cleanUp();

    Display::close();

    exit(EXIT_SUCCESS);
}


