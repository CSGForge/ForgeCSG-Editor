#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace ForgeEditor
{
    class Window
    {
    public:
        Window(uint32_t width, uint32_t height, std::string title);
        ~Window() = default;

        void Update();
        GLFWwindow *GetNativeWindow() const;
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

    private:
        GLFWwindow *mpGlfwWindow;
        uint32_t mWidth;
        uint32_t mHeight;
        std::string mTitle;
    };
}