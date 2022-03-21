#pragma once

#include <CSGForge-Core/csg.hpp>

namespace ForgeEditor
{
    class BrushManagerPanel
    {
    public:
        BrushManagerPanel(ForgeCore::World *world);
        ~BrushManagerPanel();

        void Render();

    private:
        int mSelected = -1;
        ForgeCore::Brush *mSelectedBrush;
        ForgeCore::World *mWorld;
    };
}