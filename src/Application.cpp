#include "Application.hpp"

#include <fstream>
#include <iostream>

#include <bgfx/bgfx.h>

#include "Camera.hpp"
#include "ImGuiManager.hpp"
#include "WorldManager.hpp"

namespace ForgeEditor
{
    Application *Application::sInstance = nullptr;

    Application::Application()
    {
        if (sInstance != nullptr)
        {
            // ! TODO: Shouldn't happen!
            delete sInstance;
        }

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
        auto world_manager = WorldManager();
        auto imgui_manager = ImGuiManager(mWindow->GetNativeWindow(), &world_manager);
        Camera camera = {60.0f, 0.1f, 100.f, {0.0f, 0.0f, -10.0f}};

        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            bgfx::touch(0);

            camera.Update(mWindow);
            camera.SetView(0);

            world_manager.Update();
            world_manager.Render(0);

            imgui_manager.BeginFrame();
            imgui_manager.RenderPanels();
            imgui_manager.EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            mWindow->Update();
        }
    }
}