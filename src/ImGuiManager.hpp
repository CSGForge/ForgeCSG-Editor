#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

#include "Panels/BasePanel.hpp"
#include "WorldManager.hpp"

namespace ForgeEditor
{
    class BasePanel;

    class ImGuiManager
    {
    public:
        ImGuiManager(GLFWwindow *window, WorldManager *world_manager);
        ~ImGuiManager();

        static void BeginFrame();
        void RenderPanels();
        static void EndFrame(uint32_t width, uint32_t height);
        std::vector<std::shared_ptr<BasePanel>> &GetPanels();

    private:
        std::vector<std::shared_ptr<BasePanel>> mPanels;

        void SetImGuiStyle();
    };

}