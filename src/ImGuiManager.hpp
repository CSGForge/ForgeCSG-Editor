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
        ImGuiManager(GLFWwindow *window);
        ~ImGuiManager();

        static void BeginFrame();
        void RenderPanels();
        static void EndFrame(uint32_t width, uint32_t height);
        std::vector<std::shared_ptr<BasePanel>> &GetPanels();
        static ImGuiManager &GetImGuiManager();

    private:
        static ImGuiManager *sInstance;
        std::vector<std::shared_ptr<BasePanel>> mPanels;

        void SetImGuiStyle();
    };

}