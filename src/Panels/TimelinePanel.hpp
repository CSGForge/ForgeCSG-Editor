#pragma once

#include "BasePanel.hpp"
#include "../WorldManager.hpp"

namespace ForgeEditor
{
    class TimelinePanel : BasePanel
    {
    public:
        TimelinePanel();
        ~TimelinePanel() = default;

        void Render() override;

    private:
        WorldManager *mWorldManager;
    };
}