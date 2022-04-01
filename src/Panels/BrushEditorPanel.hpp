#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class BrushEditorPanel : BasePanel
    {
    public:
        BrushEditorPanel(ImGuiManager *imGuiManager, WorldManager *world_manager);
        ~BrushEditorPanel() = default;

        void Render() override;

    private:
    };
}