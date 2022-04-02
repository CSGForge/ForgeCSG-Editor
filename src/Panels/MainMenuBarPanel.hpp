#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class MainMenuBarPanel : BasePanel
    {
    public:
        MainMenuBarPanel();
        ~MainMenuBarPanel() = default;

        void Render() override;

    private:
    };
}