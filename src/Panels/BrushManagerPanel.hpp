#pragma once

#include <CSGForge-Core/csg.hpp>

namespace ForgeEditor
{
    class BrushManagerPanel
    {
    public:
        BrushManagerPanel(ForgeCore::World *world);
        ~BrushManagerPanel() = default;

        void Render();

    private:
        int mSelected;
        ForgeCore::Brush *mSelectedBrush;
        ForgeCore::World *mWorld;
    };
}