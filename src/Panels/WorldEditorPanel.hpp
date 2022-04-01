#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class WorldEditorPanel : BasePanel
    {
    public:
        WorldEditorPanel(ImGuiManager *imGuiManager, WorldManager *world_manager);
        ~WorldEditorPanel() = default;

        void Render() override;

    private:
    };
}