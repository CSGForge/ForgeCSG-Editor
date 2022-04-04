#include "Application.hpp"

#include <bgfx/bgfx.h>

#include "ImGuiManager.hpp"
#include "WorldManager.hpp"
#include "TextureManager.hpp"

namespace ForgeEditor
{
    Application *Application::sInstance = nullptr;

    Application::Application()
    {
        if (sInstance != nullptr)
            delete sInstance;
        sInstance = this;

        mName = "CSG Forge";
        mWindow = std::make_unique<Window>(1280, 720, mName);
    }

    Application::~Application()
    {
        bgfx::shutdown();
        glfwTerminate();
    }

    void Application::Run()
    {
        auto texture_manager = TextureManager();
        auto world_manager = WorldManager();
        auto imgui_manager = ImGuiManager(mWindow->GetNativeWindow());

        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            imgui_manager.BeginFrame();
            imgui_manager.RenderPanels();
            imgui_manager.EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            world_manager.Update();
            mWindow->Update();
        }
    }

    Application &Application::GetApplication()
    {
        return *sInstance;
    }

    Window &Application::GetWindow()
    {
        return *mWindow;
    }
}