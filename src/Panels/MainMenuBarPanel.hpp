#pragma once

#include "BasePanel.hpp"
#include "../ImGuiManager.hpp"

namespace ForgeEditor
{
    class MainMenuBarPanel : BasePanel
    {
    public:
        MainMenuBarPanel(ImGuiManager *imGuiManager);
        ~MainMenuBarPanel() = default;

        void Render() override;

    private:
        ImGuiManager *mImGuiManager;
    };
}