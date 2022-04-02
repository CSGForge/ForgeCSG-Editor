#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class BrushEditorPanel : BasePanel
    {
    public:
        BrushEditorPanel();
        ~BrushEditorPanel() = default;

        void Render() override;

    private:
    };
}