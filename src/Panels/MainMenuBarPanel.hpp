#pragma once

#include "BasePanel.hpp"
#include "../ImGuiManager.hpp"
#include "../WorldManager.hpp"

namespace ForgeEditor
{
    class MainMenuBarPanel : BasePanel
    {
    public:
        MainMenuBarPanel(ImGuiManager *imGuiManager, WorldManager *world_manager);
        ~MainMenuBarPanel() = default;

        void Render() override;

    private:
        ImGuiManager *mImGuiManager;
        WorldManager *mWorldManager;
    };
}