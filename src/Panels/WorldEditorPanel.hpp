#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class WorldEditorPanel : BasePanel
    {
    public:
        WorldEditorPanel();
        ~WorldEditorPanel() = default;

        void Render() override;

    private:
    };
}