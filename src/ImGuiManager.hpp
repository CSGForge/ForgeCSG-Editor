#pragma once

#include <GLFW/glfw3.h>

namespace ForgeEditor
{
    class ImGuiManager
    {
    public:
        ImGuiManager(GLFWwindow *window);
        ~ImGuiManager();

        static void BeginFrame();
        static void EndFrame(uint32_t width, uint32_t height);

    private:
    };

}