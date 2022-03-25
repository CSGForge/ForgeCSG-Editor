#pragma once

#include <CSGForge-Core/csg.hpp>

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class BrushManagerPanel : BasePanel
    {
    public:
        BrushManagerPanel(ForgeCore::World *world);
        ~BrushManagerPanel() = default;

        void Render() override;

    private:
        int mSelected;
        ForgeCore::Brush *mSelectedBrush;
        ForgeCore::World *mWorld;
    };
}