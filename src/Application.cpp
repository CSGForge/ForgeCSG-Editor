#include "Application.hpp"

#include <imgui/imgui.h>
#include <bgfx/bgfx.h>
#include <CSGForge-Core/csg.hpp>

#include "ImGuiManager.hpp"
#include "Panels/ViewportPanel.hpp"
#include "Panels/BrushManagerPanel.hpp"

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
        auto imguiManager = ImGuiManager(mWindow->GetNativeWindow());
        auto viewport_panel = ViewportPanel();
        auto brush_manager_panel = BrushManagerPanel(&world);

        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            imguiManager.BeginFrame();

            // TODO: Move Dear ImGui stuff
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::ShowDemoWindow();
            viewport_panel.Render();
            brush_manager_panel.Render();

            imguiManager.EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            world.Update();
            mWindow->Update();
        }
    }
}