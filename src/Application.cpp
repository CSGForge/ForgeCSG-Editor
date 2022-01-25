#include "Application.hpp"

#include <imgui/imgui.h>
#include <bgfx/bgfx.h>

#include "ImGuiManager.hpp"
#include "Panels/ViewportPanel.hpp"

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
        auto imguiManager = new ImGuiManager(mWindow->GetNativeWindow());
        auto viewport_panel = new ViewportPanel();

        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            imguiManager->BeginFrame();

            bgfx::touch(0);

            // TODO: Move Dear ImGui stuff
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::ShowDemoWindow();
            viewport_panel->Render();

            imguiManager->EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            mWindow->Update();
        }
        delete imguiManager;
    }
}