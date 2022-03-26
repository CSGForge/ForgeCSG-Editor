#include "Application.hpp"

#include <fstream>
#include <iostream>

#include <imgui/imgui.h>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <CSGForge-Core/csg.hpp>

#include "Camera.hpp"
#include "ImGuiManager.hpp"
#include "Mesh/Model.hpp"

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
        auto world = ForgeCore::World();
        auto imguiManager = ImGuiManager(mWindow->GetNativeWindow(), &world);
        auto model = Model(world);
        Camera camera = {60.0f, 0.1f, 100.f, {0.0f, 0.0f, -10.0f}};

        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            bgfx::touch(0);

            camera.Update(mWindow);
            camera.SetView(0);
            model.Render(0);

            imguiManager.BeginFrame();
            imguiManager.RenderPanels();
            imguiManager.EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            auto start = clock();
            world.Update();
            if (world.Modified())
            {
                model = Model(world);
                auto end = clock();
                printf("Update took %.3f seconds\n", (end - start) / (double)CLOCKS_PER_SEC);
            }
            mWindow->Update();
        }
    }
}