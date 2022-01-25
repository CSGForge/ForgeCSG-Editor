#include <iostream>

#include <imgui/imgui.h>
#include <bgfx/bgfx.h>

#include "ImGuiManager.hpp"
#include "Window.hpp"

int main(int argc, char *argv[])
{
    // TODO: Move Dear ImGui stuff
    auto window = new ForgeEditor::Window(1280, 720, "CSG Forge");
    auto imguiManager = new ForgeEditor::ImGuiManager(window->GetNativeWindow());

    while (!glfwWindowShouldClose(window->GetNativeWindow()))
    {
        imguiManager->BeginFrame();

        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 0, 0x0f, "Epic");

        // TODO: Move Dear ImGui stuff
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::ShowDemoWindow();

        imguiManager->EndFrame(window->GetWidth(), window->GetHeight());

        window->Update();
    }

    delete imguiManager;
    bgfx::shutdown();
    glfwTerminate();
    return 0;
}