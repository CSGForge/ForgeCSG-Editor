#include "ImGuiManager.hpp"

#include <imgui/imgui.h>

#include "imgui_backends/imgui_impl_glfw.hpp"
#include "imgui_backends/imgui_impl_bgfx.hpp"
#include "Panels/ViewportPanel.hpp"
#include "Panels/BrushEditorPanel.hpp"
#include "Panels/MainMenuBarPanel.hpp"
#include "Panels/TimelinePanel.hpp"
#include "Panels/WorldEditorPanel.hpp"

namespace ForgeEditor
{
    ImGuiManager::ImGuiManager(GLFWwindow *window, WorldManager *world_manager)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        SetImGuiStyle();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_Implbgfx_Init(255);

        mPanels.emplace_back(std::shared_ptr<BasePanel>((BasePanel *)new ViewportPanel()));
        mPanels.emplace_back(std::shared_ptr<BasePanel>((BasePanel *)new BrushEditorPanel(this, world_manager)));
        mPanels.emplace_back(std::shared_ptr<BasePanel>((BasePanel *)new MainMenuBarPanel(this, world_manager)));
        mPanels.emplace_back(std::shared_ptr<BasePanel>((BasePanel *)new TimelinePanel(this, world_manager)));
        mPanels.emplace_back(std::shared_ptr<BasePanel>((BasePanel *)new WorldEditorPanel(this, world_manager)));
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
        // ImGui::ShowDemoWindow();
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

    std::vector<std::shared_ptr<BasePanel>> &ImGuiManager::GetPanels()
    {
        return mPanels;
    }

    void ImGuiManager::SetImGuiStyle()
    {
        // Style modified from https://github.com/ocornut/imgui/issues/707#issuecomment-917151020
        ImVec4 *colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.71f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.86f, 0.61f, 0.33f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.86f, 0.61f, 0.33f, 0.54f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.61f, 0.33f, 0.92f);
        colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.71f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.71f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.92f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.86f, 0.61f, 0.33f, 0.54f);
        colors[ImGuiCol_TabActive] = ImVec4(0.86f, 0.61f, 0.33f, 0.36f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_DockingPreview] = ImVec4(0.86f, 0.61f, 0.33f, 0.54f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.86f, 0.61f, 0.33f, 0.54f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.12f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.86f, 0.61f, 0.33f, 1.00f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.86f, 0.61f, 0.33f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.86f, 0.61f, 0.33f, 1.00f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.51f, 0.55f, 0.60f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.51f, 0.55f, 0.60f, 0.35f);

        ImGuiStyle &style = ImGui::GetStyle();
        style.CellPadding = ImVec2(4.00f, 3.00f);
        style.WindowRounding = 3;
        style.ChildRounding = 3;
        style.FrameRounding = 3;
        style.PopupRounding = 3;
        style.GrabRounding = 3;

        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->ClearFonts();
        io.Fonts->AddFontFromFileTTF("res/fonts/NotoSans-Regular.ttf", 17);
        io.Fonts->Build();
        // TODO: Add icons?
    }
}