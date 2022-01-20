#include <iostream>

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

int main(int argc, char *argv[]) {
    std::cout << "Hi!" << std::endl;

    bgfx::init();

    return 0;
}