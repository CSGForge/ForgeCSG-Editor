#include "Window.hpp"

#include <string>

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

namespace ForgeEditor
{
    static bool sGlfwInitialised = false;

    Window::Window(uint32_t width, uint32_t height, std::string title)
        : mWidth(width), mHeight(height), mTitle(title)
    {
        if (!sGlfwInitialised)
        {
            if (!glfwInit())
                ; // TODO: ERROR!
            sGlfwInitialised = true;
        }

        mpGlfwWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);

        // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
        // Most graphics APIs must be used on the same thread that created the window.
        bgfx::renderFrame();
        // Initialize bgfx using the native window handle and window resolution.
        bgfx::Init init;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        init.platformData.ndt = glfwGetX11Display();
        init.platformData.nwh = (void *)(uintptr_t)glfwGetX11Window(mpGlfwWindow);
#elif BX_PLATFORM_OSX
        init.platformData.nwh = glfwGetCocoaWindow(mpGlfwWindow);
#elif BX_PLATFORM_WINDOWS
        init.platformData.nwh = glfwGetWin32Window(mpGlfwWindow);
#endif
        init.resolution.width = mWidth;
        init.resolution.height = mHeight;
        init.resolution.reset = BGFX_RESET_VSYNC;
        init.type = bgfx::RendererType::OpenGL; // Would be nice to be able to use whatever
        if (!bgfx::init(init))
            ; // TODO: ERROR!

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
    }

    void Window::Update()
    {
        glfwPollEvents();

        // Handle window resize.
        int new_width = mWidth, new_height = mHeight;
        glfwGetWindowSize(mpGlfwWindow, &new_width, &new_height);
        if (new_width != mWidth || new_height != mHeight)
        {
            mWidth = new_width;
            mHeight = new_height;
            bgfx::reset(mWidth, mHeight, BGFX_RESET_VSYNC);
            bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
        }

        bgfx::frame();
    }

    GLFWwindow *Window::GetNativeWindow() const
    {
        return mpGlfwWindow;
    }

    uint32_t Window::GetWidth() const
    {
        return mWidth;
    }

    uint32_t Window::GetHeight() const
    {
        return mHeight;
    }
}