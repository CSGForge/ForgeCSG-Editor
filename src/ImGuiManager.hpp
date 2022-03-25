#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>
#include <CSGForge-Core/csg.hpp>

#include "Panels/BasePanel.hpp"

namespace ForgeEditor
{
    class ImGuiManager
    {
    public:
        ImGuiManager(GLFWwindow *window, ForgeCore::World *world);
        ~ImGuiManager();

        static void BeginFrame();
        void RenderPanels();
        static void EndFrame(uint32_t width, uint32_t height);
        std::vector<std::shared_ptr<BasePanel>> &GetPanels();

    private:
        std::vector<std::shared_ptr<BasePanel>> mPanels;
    };

}