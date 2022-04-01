#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class TimelinePanel : BasePanel
    {
    public:
        TimelinePanel(ImGuiManager *imGuiManager, WorldManager *world_manager);
        ~TimelinePanel() = default;

        void Render() override;

    private:
    };
}