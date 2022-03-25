#include "ImGuiManager.hpp"

#include <imgui/imgui.h>

#include "imgui_backends/imgui_impl_glfw.hpp"
#include "imgui_backends/imgui_impl_bgfx.hpp"
#include "Panels/ViewportPanel.hpp"
#include "Panels/BrushManagerPanel.hpp"
#include "Panels/MainMenuBarPanel.hpp"

namespace ForgeEditor
{
    ImGuiManager::ImGuiManager(GLFWwindow *window, ForgeCore::World *world)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        // ImGuiStyle &style = ImGui::GetStyle();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_Implbgfx_Init(255);

        mPanels.emplace_back(std::unique_ptr<BasePanel>((BasePanel *)new ViewportPanel()));
        mPanels.emplace_back(std::unique_ptr<BasePanel>((BasePanel *)new BrushManagerPanel(world)));
        mPanels.emplace_back(std::unique_ptr<BasePanel>((BasePanel *)new MainMenuBarPanel()));
    }

    ImGuiManager::~ImGuiManager()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_Implbgfx_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiManager::BeginFrame()
    {
        ImGui_ImplGlfw_NewFrame();
        ImGui_Implbgfx_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiManager::RenderPanels()
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        for (auto &&panel : mPanels)
            panel->Render();
    }

    void ImGuiManager::EndFrame(uint32_t width, uint32_t height)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(width, height);

        ImGui::Render();
        ImGui_Implbgfx_RenderDrawData(ImGui::GetDrawData());
    }
}